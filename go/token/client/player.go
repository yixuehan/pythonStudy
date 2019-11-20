package main

import (
	"fmt"
	"time"
	"token/define"
)

var players = map[int32]*define.PlayerInfo{}
var clientCount = 10

func receive(client *define.PlayerInfo) {
	str, err := client.ReceiveToken()
	if err != nil {
		delete(players, client.Location)
	}
	fmt.Printf("%s\n", str)
}

func main() {
	var playerNum int32
	for i := 0; i < clientCount; i++ {
		client := &define.PlayerInfo{}
		client.Connect(":8888")
		if client.Valid {
			client.Location = playerNum
			players[playerNum] = client
			playerNum++
			go client.ReceiveToken()
		}
	}
	for len(players) > 0 {
		fmt.Printf("clients:%d\n", len(players))
		time.Sleep(time.Second * 1)
		for i, player := range players {
			if player.Done {
				delete(players, i)
			}
		}
	}
}
