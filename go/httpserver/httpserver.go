package httpserver

import (
	"crypto/tls"
	"fmt"
	"net"
	"net/http"
	"strings"
	"sync"
	"time"

	"github.com/gorilla/mux"
	"golang.org/x/net/http2"
)

const (
	Default_H2    = false
	Default_Trace = false
	idleTimeout   = 1 * time.Minute
	activeTimeout = 2 * time.Minute
)

type HttpServer struct {
	trace bool
	h2    bool

	streams uint32

	r         *mux.Router
	srv       *http.Server
	tlsConfig *tls.Config
}

// TODO: put this into the standard library and actually send
// PING frames and GOAWAY, etc: golang.org/issue/14204
func idleTimeoutHook() func(net.Conn, http.ConnState) {
	var mu sync.Mutex
	m := map[net.Conn]*time.Timer{}
	return func(c net.Conn, cs http.ConnState) {
		mu.Lock()
		defer mu.Unlock()
		if t, ok := m[c]; ok {
			delete(m, c)
			t.Stop()
		}
		var d time.Duration
		switch cs {
		case http.StateNew, http.StateIdle:
			d = idleTimeout
		case http.StateActive:
			d = activeTimeout
		default:
			return
		}
		m[c] = time.AfterFunc(d, func() {
			fmt.Printf("closing idle conn local %v remote %v, after %v\n", c.LocalAddr(), c.RemoteAddr(), d)
			_ = c.Close()
		})
	}
}

func HostPort(host, port string) func(*HttpServer) {
	return func(s *HttpServer) {
		s.srv.Addr = net.JoinHostPort(host, port)
	}
}

func Trace(t bool) func(*HttpServer) {
	return func(s *HttpServer) {
		s.trace = t
	}
}

func HTTP2(h2 bool) func(*HttpServer) {
	return func(s *HttpServer) {
		s.h2 = h2
	}
}

func ReadTimeout(t time.Duration) func(*HttpServer) {
	return func(s *HttpServer) {
		s.srv.ReadTimeout = t
	}
}

func WriteTimeout(t time.Duration) func(*HttpServer) {
	return func(s *HttpServer) {
		s.srv.WriteTimeout = t
	}
}

func MaxConcurrentStreams(m uint32) func(*HttpServer) {
	return func(s *HttpServer) {
		s.streams = m
	}
}

func TLSConfig(t *tls.Config) func(*HttpServer) {
	return func(s *HttpServer) {
		s.tlsConfig = t.Clone()
		s.srv.TLSConfig = s.tlsConfig
	}
}

func traceHttpRouteTime(trace bool, method, url string, began time.Time) {
	if trace {
		dur := time.Now().Sub(began)
		fmt.Println(method, " ", url, "------delay time-----********", dur)
	}
}

func PathFunc(url, methods string, f func(http.ResponseWriter, *http.Request)) func(*HttpServer) {
	return func(s *HttpServer) {
		m := make([]string, 0)
		for _, v := range strings.Split(methods, ",") {
			if v = strings.TrimSpace(v); v != "" {
				m = append(m, v)
			}
		}
		fmt.Println(methods, " ", url)

		s.r.Path(url).Methods(m...).HandlerFunc(func(resp http.ResponseWriter, req *http.Request) {
			defer traceHttpRouteTime(s.trace, req.Method, req.URL.String(), time.Now())
			f(resp, req)
		})

	}
}

func PathPrefixFunc(url, methods string, f func(http.ResponseWriter, *http.Request)) func(*HttpServer) {
	return func(s *HttpServer) {
		m := make([]string, 0)
		for _, v := range strings.Split(methods, ",") {
			if v = strings.TrimSpace(v); v != "" {
				m = append(m, v)
			}
		}
		fmt.Println(methods, " ", url)

		s.r.PathPrefix(url).Methods(m...).HandlerFunc(func(resp http.ResponseWriter, req *http.Request) {
			defer traceHttpRouteTime(s.trace, req.Method, req.URL.String(), time.Now())
			f(resp, req)
		})
	}
}

func InitHttpServer(opts ...func(*HttpServer)) *HttpServer {
	s := &HttpServer{
		h2:        Default_H2,
		r:         mux.NewRouter(),
		tlsConfig: nil,
		trace:     Default_Trace,
		srv: &http.Server{
			ConnState: idleTimeoutHook(),
		},
	}

	s.srv.Handler = s.r

	for _, opt := range opts {
		opt(s)
	}

	return s
}

func (s *HttpServer) Run() {
	if s.tlsConfig != nil {
		s.runHttpWithTLS(s.h2)
	} else if s.h2 {
		s.runHttp2WithoutTLS()
	} else {
		s.runHttpWithoutTLS()
	}
}

//support http/2.0
func (s *HttpServer) runHttp2WithoutTLS() {
	httpListener, err := net.Listen("tcp", s.srv.Addr)
	if err != nil {
		panic(err.Error())
	}

	fmt.Printf("Listening on %s Http2WithoutTLS\n", s.srv.Addr)

	opts := &http2.ServeConnOpts{
		BaseConfig: s.srv,
	}

	srvH2 := &http2.Server{
		MaxConcurrentStreams: s.streams,
	}

	var tempDelay time.Duration // how long to sleep on accept failure

	go func() {
		for {
			rw, e := httpListener.Accept()
			if e != nil {
				if ne, ok := e.(net.Error); ok && ne.Temporary() {
					if tempDelay == 0 {
						tempDelay = 5 * time.Millisecond
					} else {
						tempDelay *= 2
					}
					if max := 1 * time.Second; tempDelay > max {
						tempDelay = max
					}
					time.Sleep(tempDelay)
					continue
				}
				fmt.Println(e.Error())
				break
			}
			tempDelay = 0
			fmt.Printf("local: %s, remote: %s\n", rw.LocalAddr().String(), rw.RemoteAddr().String())
			go srvH2.ServeConn(rw, opts)
		}
	}()
}

func strSliceContains(ss []string, s string) bool {
	for _, v := range ss {
		if v == s {
			return true
		}
	}
	return false
}

func (s *HttpServer) runHttpWithTLS(h2 bool) {
	if h2 {
		srvH2 := &http2.Server{
			MaxConcurrentStreams: s.streams,
		}

		if err := http2.ConfigureServer(s.srv, srvH2); err != nil {
			panic(err)
		}
	}

	if !strSliceContains(s.srv.TLSConfig.NextProtos, "http/1.1") {
		s.srv.TLSConfig.NextProtos = append(s.srv.TLSConfig.NextProtos, "http/1.1")
	}

	httpListener, err := tls.Listen("tcp", s.srv.Addr, s.tlsConfig)
	if err != nil {
		panic(err.Error())
	}

	go func() {
		fmt.Printf("Listening on %s HttpWithTLS\n", s.srv.Addr)
		if err := s.srv.Serve(httpListener); err != nil {
			fmt.Printf("Listenting on %s HttpWithTLS is exiting, %s\n", s.srv.Addr, err.Error())
		}
	}()
}

/*
//support https/1 and https/2.0
func (s *Server) runHttpWithTLS_1() {
	hp := net.JoinHostPort(s.opts.Host, strconv.Itoa(s.opts.PortHttpWithTLS))

	srv := &http.Server{
		Addr:         hp,
		ConnState:    idleTimeoutHook(),
		Handler:      s.r,
		ReadTimeout:  HTTP_SERVER_READ_TIMEOUT,
		WriteTimeout: HTTP_SERVER_WRITE_TIMEOUT,
		//	MaxHeaderBytes: 1 << 20,
	}

	srvH2 := &http2.Server{
		MaxConcurrentStreams: s.opts.Http2MaxStreamNum,
	}

	http2.ConfigureServer(srv, srvH2)

	go func() {
		LOG.Warningf("Listening on %s HttpWithTLS", hp)
		//srv.Serve(httpListener)
		err := srv.ListenAndServeTLS(s.opts.TLSCertFile, s.opts.TLSKeyFile)
		LOG.Infof("Listening exit %s, %s", hp, err.Error())
	}()
}*/

//only http/1.1
func (s *HttpServer) runHttpWithoutTLS() {
	httpListener, err := net.Listen("tcp", s.srv.Addr)
	if err != nil {
		panic(err.Error())
	}

	go func() {
		fmt.Printf("Listening on %s HttpWithoutTLS\n", s.srv.Addr)
		//if err := s.srv.ListenAndServe(); err != nil {
		if err := s.srv.Serve(httpListener); err != nil {
			fmt.Printf("Listenting on %s HttpWithTLS is exiting, %s\n", s.srv.Addr, err.Error())
		}
	}()
}

func (s *HttpServer) Stop() {
	if s.srv != nil {
		_ = s.srv.Close()
	}
}

/*


//support https/1 and https/2.0
func (s *Server) runHttpWithTLS_1() {
	/*tlsConfig, err := s.genTLSConfig(tc)
	if err != nil {
		panic(err.Error())
	}

	httpListener, err := tls.Listen("tcp", addr, tlsConfig)
	if err != nil {
		panic(err.Error())
	}*/

/*
	hp := net.JoinHostPort(s.opts.Host, strconv.Itoa(s.opts.PortHttpWithTLS))

	srv := &http.Server{
		Addr:         hp,
		ConnState:    idleTimeoutHook(),
		Handler:      s.r,
		ReadTimeout:  HTTP_SERVER_READ_TIMEOUT,
		WriteTimeout: HTTP_SERVER_WRITE_TIMEOUT,
		//	MaxHeaderBytes: 1 << 20,
	}

	srvH2 := &http2.Server{
		MaxConcurrentStreams: s.opts.Http2MaxStreamNum,
	}

	http2.ConfigureServer(srv, srvH2)

	go func() {
		LOG.Warningf("Listening on %s HttpWithTLS", hp)
		//srv.Serve(httpListener)
		err := srv.ListenAndServeTLS(s.opts.TLSCertFile, s.opts.TLSKeyFile)
		LOG.Infof("Listening exit %s, %s", hp, err.Error())
	}()
}

*/
