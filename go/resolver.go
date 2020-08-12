package main

import (
	"fmt"
	"net"
	"os"
)

/**
 * 根据IP和掩码获得网络
 */
func main() {
	//name := "192.168.1.97"

	ip, err := net.ResolveIPAddr("ip", "www.baidu.com")
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Fprintf(os.Stdout, "ip: %s\n", ip.String()) // 192.168.1.0

	// ip: 		192.168.1.97
	// mask:	255.255.255.0
	// network:	192.168.1.0
}
