package main

import (
	"fmt"
	"net"
	"os"
)

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error:%s\n", err.Error())
		os.Exit(1)
	}
}

func main() {
	service := ":1200"
	tcpAddr, err := net.ResolveTCPAddr("ip4", service)
	checkError(err)
	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		conn.Read()

	}
}
