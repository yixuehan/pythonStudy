package main

import (
	"fmt"
	"net"
	"strings"
)

type Client struct {
	conn net.Conn
	done bool
}

func (c *Client) Connect() {
	var err error
	c.conn, err = net.Dial("tcp", ":8888")
	if err != nil {
		fmt.Println(err)
	}
}

func (c *Client) Read() {
	buf := make([]byte, 32)
	// buf := []byte{}
	for {
		_, err := c.conn.Read(buf)
		if err != nil {
			str := string(buf)
			if strings.Index(str, "token") != -1 {
				c.done = true
				c.conn.Close()
			}
			fmt.Println(str)
		} else {
			c.conn.Close()
		}
	}
}

var players = map[int]*Client{}
var clientCount = 1000

func main() {
	for i := 1; i < clientCount; i++ {
		client := &Client{}
		players[i] = client
		client.Connect()
		go client.Read()
	}
	for len(players) > 0 {
		for i, player := range players {
			if player.done {
				delete(players, i)
			}
		}
	}
}
