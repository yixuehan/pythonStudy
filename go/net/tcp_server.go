package main

import (
	"fmt"
	"net"
	"os"

	"git.ucloudadmin.com/securityhouse/dataflow/pkg/tcp"
)

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error:%s\n", err.Error())
		os.Exit(1)
	}
}

func handle(conn net.Conn) {
	var buf []byte
	buf = make([]byte, 4096000)
	n, _ := tcp.ReadWithLenHead(conn, buf, 8)
	fmt.Println(n)
	// time.Sleep(2 * time.Second)
	conn.Close()
}

// func handleSignal(c chan os.Signal) {
// 	// var sig os.Signal
// 	for {
// 		<-c
// 		// fmt.Println(sig.String())
// 	}
// }

func main() {
	service := ":1200"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", service)
	checkError(err)
	listener, err := net.ListenTCP("tcp4", tcpAddr)
	checkError(err)

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		go handle(conn)
	}
}
