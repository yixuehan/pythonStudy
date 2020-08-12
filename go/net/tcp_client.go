package main

import (
	"fmt"
	"net"
	"os"
	"os/signal"
	"syscall"

	"git.ucloudadmin.com/securityhouse/dataflow/pkg/tcp"
)

func handleSignal(c chan os.Signal) {
	for {
		switch <-c {
		case syscall.SIGINT:
			fmt.Println("sigint")
		}

	}
}

func main() {
	c := make(chan os.Signal, 1)
	signal.Notify(c, syscall.SIGINT)
	go handleSignal(c)
	conn, _ := net.Dial("tcp4", "127.0.0.1:1200")
	buf := make([]byte, 4096000)
	for {
		n, err := tcp.WriteWithLenHead(conn, buf, 8)
		// n, err := conn.Write(buf)
		if err != nil {
			fmt.Println(err)
			fmt.Println(n)
		} else {
			fmt.Println("success:", n)
		}
		break
	}
	conn.Close()
}
