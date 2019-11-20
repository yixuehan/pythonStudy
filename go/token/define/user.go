package define

import (
	"errors"
	"fmt"
	"net"
	"strings"
)

// 玩家连接信息
type PlayerInfo struct {
	UserID   string
	Conn     net.Conn
	Location int32
	Done     bool
	Valid    bool
}

func (p *PlayerInfo) SendMsg(msg string) {
	fmt.Printf("sendmsg:%s\n", msg)
	p.Conn.Write([]byte(msg))
}

func (p *PlayerInfo) Connect(addr string) {
	var err error
	p.Conn, err = net.Dial("tcp", addr)
	if err != nil {
		fmt.Println(err)
		return
	}
	p.Valid = true
}

func (p *PlayerInfo) ReceiveToken() (string, error) {
	buf := make([]byte, 64)
	// buf := []byte{}
	for {
		rb, err := p.Conn.Read(buf)
		if rb == 0 {
			fmt.Printf("服务端关闭\n")
			err = errors.New("服务端关闭")
			return "", err

		}
		if err == nil {
			str := string(buf)
			fmt.Println("receive:", str)
			if strings.Index(str, "token") != -1 {
				p.Conn.Close()
				p.Done = true
				return str, nil
			}
		} else {
			p.Conn.Close()
			fmt.Printf("%v\n", err)
			return "", err
		}
	}

}
