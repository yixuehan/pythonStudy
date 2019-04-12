package httpclient

import (
	"crypto/tls"
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"net/http"
	"time"

	"golang.org/x/net/http2"
)

var (
	DefaultTimeout     = 30 * time.Second
	DefaultTLSConfig   = &tls.Config{InsecureSkipVerify: true}
	DefaultConnections = 2
)

type NHeader map[string]string

type HttpClient struct {
	trace  bool
	client *http.Client
	dialer *net.Dialer
}

type HttpRespData struct {
	StatusCode  int
	Protocol    string
	ContentType string
	Body        []byte
}

func (h *HttpRespData) String() string {
	data, err := json.Marshal(h)
	if err == nil {
		return string(data)
	}

	return err.Error()
}

func (h *HttpRespData) SimpleString() string {
	return fmt.Sprintf("{StatusCode: %d, Protocol: %s, ContentType: %s}",
		h.StatusCode, h.Protocol, h.ContentType)
}

func InitHttpClient(opts ...func(*HttpClient)) *HttpClient {
	a := &HttpClient{
		trace: false,
	}
	a.dialer = &net.Dialer{
		KeepAlive: 30 * time.Second,
		Timeout:   DefaultTimeout,
	}
	a.client = &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyFromEnvironment,
			Dial:  a.dialer.Dial,
			ResponseHeaderTimeout: DefaultTimeout,
			TLSClientConfig:       DefaultTLSConfig,
			TLSHandshakeTimeout:   10 * time.Second,
			MaxIdleConnsPerHost:   DefaultConnections,
		},
	}
	for _, opt := range opts {
		opt(a)
	}

	return a
}

func Connections(n int) func(*HttpClient) {
	return func(a *HttpClient) {
		tr := a.client.Transport.(*http.Transport)
		tr.MaxIdleConnsPerHost = n
	}
}

func Trace(b bool) func(*HttpClient) {
	return func(a *HttpClient) {
		a.trace = b
	}
}

func Timeout(d time.Duration) func(*HttpClient) {
	return func(a *HttpClient) {
		tr := a.client.Transport.(*http.Transport)
		tr.ResponseHeaderTimeout = d
		a.dialer.Timeout = d
		tr.Dial = a.dialer.Dial
	}
}

func KeepAlive(keepalive bool) func(*HttpClient) {
	return func(a *HttpClient) {
		tr := a.client.Transport.(*http.Transport)
		tr.DisableKeepAlives = !keepalive
		if !keepalive {
			a.dialer.KeepAlive = 0
			tr.Dial = a.dialer.Dial
		}
	}
}

func SupportH2c() func(*HttpClient) {
	return func(a *HttpClient) {
		tr := &http2.Transport{
			AllowHTTP: true,
			DialTLS: func(netw, addr string, cfg *tls.Config) (net.Conn, error) {
				return a.dialer.Dial(netw, addr)
			},
		}
		a.client.Transport = tr
	}
}

func TLSConfig(c *tls.Config) func(*HttpClient) {
	return func(a *HttpClient) {
		tr := a.client.Transport.(*http.Transport)
		tr.TLSClientConfig = c
	}
}

func HTTP2(enabled bool) func(*HttpClient) {
	return func(a *HttpClient) {
		if tr := a.client.Transport.(*http.Transport); enabled {
			if err := http2.ConfigureTransport(tr); err != nil {
				fmt.Println("Can not configure HTTP2 ", err)
				panic(err)
			}
		} else {
			tr.TLSNextProto = map[string]func(string, *tls.Conn) http.RoundTripper{}
		}
	}
}

func (c *HttpClient) do(req *http.Request) (resp *HttpRespData, err error) {
	if resp, err := c.client.Do(req); err == nil {
		defer func() {
			if err := resp.Body.Close(); err != nil {
				fmt.Println("Close http response error ", err)
			}
		}()
		respbody, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			return nil, err
		}

		header := resp.Header.Get("Content-Type")
		if c.trace {
			fmt.Println(resp.Status, " ", resp.Proto)
		}
		return &HttpRespData{
			StatusCode:  resp.StatusCode,
			Protocol:    resp.Proto,
			ContentType: header,
			Body:        respbody,
		}, nil

	} else {
		return nil, err
	}
}

func (c *HttpClient) HttpDo(method, url string, hdr NHeader, body io.Reader) (resp *HttpRespData, err error) {
	req, err := http.NewRequest(method, url, body)
	if err != nil {
		return nil, err
	}
	for h, v := range hdr {
		req.Header.Set(h, v)
	}

	return c.do(req)
}

func (c *HttpClient) HttpDoJsonBody(method, url string, body io.Reader) (resp *HttpRespData, err error) {
	req, err := http.NewRequest(method, url, body)
	if err != nil {
		return nil, err
	}
	req.Header.Set("Content-Type", "application/json")

	return c.do(req)
}
