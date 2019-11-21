package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"syscall"
	"token/define"
)

var clientCount int32 = 1000

type TokenClient struct {
	players    map[int32]*define.PlayerInfo
	tokenFile  *os.File
	playerNum  int32
	playerChan chan *define.PlayerInfo
	doneChan   chan int32
	stopChan   chan bool
	clientNums int32
}

func (t *TokenClient) Init() {
	var err error
	// filename := fmt.Sprintf("token_%v.txt", time.Now().UnixNano())
	filename := fmt.Sprintf("token_%v.txt", os.Getpid())
	t.tokenFile, err = os.Create(filename)
	if err != nil {
		log.Fatal(err)
	}
	t.players = make(map[int32]*define.PlayerInfo, 0)
	t.doneChan = make(chan int32, clientCount)
	t.stopChan = make(chan bool, 1)
	t.playerChan = make(chan *define.PlayerInfo, clientCount)
}

func (t *TokenClient) ReceiveToken(player *define.PlayerInfo) {
	str, err := player.ReceiveToken()
	if err != nil {
		fmt.Printf("error %v\n", err)
	} else {
		// fmt.Printf("%s\n", str)
		t.tokenFile.WriteString(fmt.Sprintf("%s\n", str))
	}
	t.doneChan <- player.Location
}

// 模拟客户端连接
func (t *TokenClient) ProducePlayer() {
	t.tokenFile.WriteString(fmt.Sprintf("生产[%d]个玩家\n", clientCount))
	t.clientNums = clientCount
	var i int32
	for i = 0; i < clientCount; i++ {
		client := &define.PlayerInfo{}
		client.Connect(":8888")
		if client.Valid {
			// go func() {
			client.Location = t.playerNum
			t.playerNum++
			t.playerChan <- client
			// }()
		}
	}
	t.tokenFile.WriteString(fmt.Sprintf("生产[%d]个玩家完成\n", clientCount))
}

func (t *TokenClient) Stop() {
	fmt.Printf("模拟关闭\n")
	t.tokenFile.Close()
	t.stopChan <- true
}

func (t *TokenClient) Process() {
	var donePos int32
	var player *define.PlayerInfo
	var stop bool
	fmt.Printf("开始处理请求\n")
	for !stop {
		select {
		case player = <-t.playerChan:
			t.players[player.Location] = player
			go t.ReceiveToken(player)
		case donePos = <-t.doneChan:
			t.players[donePos].Conn.Close()
			delete(t.players, donePos)
			t.clientNums--
			if t.clientNums == 0 {
				// signal.Stop(syscall.SIGINT)
				sigChan <- syscall.SIGINT
				// t.Stop()
			}
		case stop = <-t.stopChan:
			fmt.Printf("select break\n")
			break
		}
	}
}

var sigChan = make(chan os.Signal, 1)
var doneChan = make(chan int32, 1)

func main() {
	c := &TokenClient{}
	c.Init()
	go c.ProducePlayer()
	// 信号Ctrl + C
	signal.Notify(sigChan, syscall.SIGINT)
	go func() {
		sig := <-sigChan
		if sig == syscall.SIGINT {
			c.Stop()
		}
		doneChan <- 0
	}()
	c.Process()
	<-doneChan
}
