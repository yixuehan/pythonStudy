package main

import (
	"fmt"
	"net"
	"sync"
	"time"
	"token/define"
)

const (
	unitSize = 1000
)

type Array struct {
	popCount  int32
	capacity  int32
	pushCount int32
	memberss  [][unitSize]interface{}
	mtx       sync.Mutex
}

func (a *Array) ConvertIndex(index int32) int32 {
	index = index - (a.popCount / unitSize * unitSize) + a.popCount%unitSize
	return index
}

func (a *Array) Members() [][unitSize]interface{} {
	return a.memberss
}

func (a *Array) size() {
	// fmt.Println("capacity:", a.capacity, len(a.memberss)*unitSize)
}

func (a *Array) pop() {
	if a.popCount == a.pushCount {
		return
	}
	if a.popCount > a.pushCount {
		panic("逻辑错误")
	}
	a.popCount++
	// atomic.AddInt32(&(a.popCount), 1)
	if a.popCount%unitSize == 0 {
		a.memberss = a.memberss[1:]
		a.capacity -= unitSize
	}
}

func (a *Array) Pop() {
	a.mtx.Lock()
	defer a.mtx.Unlock()
	a.pop()
}

func (a *Array) push(arg interface{}) int32 {
	// pushCount = atomic.AddInt32(&(a.pushCount), 1)
	a.pushCount++
	if (a.pushCount-1)%unitSize == 0 {
		a.memberss = append(a.memberss, [unitSize]interface{}{})
		a.capacity += unitSize
	}
	index := a.ConvertIndex(a.pushCount - 1)
	i := index / unitSize
	j := index % unitSize
	// fmt.Printf("第[%d]个玩家，位置是[%d][%d]", a.pushCount, i, j)
	fmt.Printf("push:[%d][%d][%v]\n", i, j, arg)
	a.memberss[i][j] = arg
	return a.pushCount
}

func (a *Array) Push(arg interface{}) int32 {
	a.mtx.Lock()
	defer a.mtx.Unlock()
	return a.push(arg)
}

func (a *Array) get(index int32) interface{} {
	indexNew := a.ConvertIndex(index)
	i := indexNew / unitSize
	j := indexNew % unitSize
	fmt.Printf("Get:[%d][%d][%d][%d]\n", index, indexNew, i, j)

	return a.memberss[i][j]
}

func (a *Array) Get(index int32) interface{} {
	a.mtx.Lock()
	defer a.mtx.Unlock()
	return a.get(index)
}

type Players struct {
	Array
}

func (p *Players) donePlayers() int32 {
	return p.popCount
}

func (p *Players) allPlayers() int32 {
	return p.pushCount
}

func (p *Players) LeftPlayers() int32 {
	p.mtx.Lock()
	defer p.mtx.Unlock()
	return p.leftPlayers()
}
func (p *Players) leftPlayers() int32 {
	// fmt.Printf("push[%d] pop[%d]\n", p.pushCount, p.popCount)
	return p.pushCount - p.popCount
}

func (p *Players) GetToken() {
	p.mtx.Lock()
	defer p.mtx.Unlock()
	fmt.Printf("gettoken: push[%d] pop[%d]\n", p.pushCount, p.popCount)
	if p.popCount == p.pushCount {
		return
	}

	player := p.get(0).(*define.PlayerInfo)
	player.SendMsg(fmt.Sprintf("玩家[%d]token [%v]", player.Location, player.Location))
	player.Conn.Close()
	p.pop()
}

func (p *Players) Notify() {
	p.mtx.Lock()
	defer p.mtx.Unlock()
	var i int32
	fmt.Printf("通知排队的[%d]位玩家\n", p.leftPlayers())
	for i = 0; i < p.leftPlayers(); i++ {
		player := p.get(i).(*define.PlayerInfo)
		msg := fmt.Sprintf("玩家[%d]当前排在第[%d]位", player.Location, player.Location-p.popCount)
		// fmt.Println(msg)
		player.SendMsg(msg)
	}
}

// var index int32
// var done int32
var players Players

func userHandle(conn net.Conn) {
	userInfo := &define.PlayerInfo{
		Conn: conn,
	}
	// atomic.AddInt32(&index, 1)
	userInfo.Location = players.Push(userInfo)
}

// var userQueue = sync.Map[int32]define.PlayerInfo{}

func ServerRun() {
	l, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Printf("%v\n", err)
		return
	}
	run <- 0
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("accept 失败:%v\n", err)
			continue
		}
		fmt.Printf("accept 新用户\n")
		go userHandle(conn)
	}
}

func producer() {
	for {
		players.Push(&define.PlayerInfo{})
	}
}

func consumer() {
	for {
		time.Sleep(time.Second * 1)
		players.GetToken()
	}
}

func printPlayers() {
	for {
		time.Sleep(time.Second * 1)
		fmt.Printf("共接入[%d]玩家\n", players.allPlayers())
		fmt.Printf("待处理玩家[%d]\n", players.leftPlayers())
		players.size()
		players.Notify()
	}
}

var run = make(chan int, 0)

func main() {
	fmt.Println("server running...")
	go ServerRun()
	<-run
	for i := 0; i < 1; i++ {
		// go producer()
		go consumer()
	}
	go printPlayers()

	select {}
}
