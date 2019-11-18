package main

import (
	"fmt"
	"net"
	"sync"
	"time"
)

const (
	unitSize = 1000
)

type UserInfo struct {
	UserID string
	Conn   net.Conn
	Index  int32
}

func (u *UserInfo) sendMsg(msg string) {
	u.Conn.Write([]byte(msg))
}

type Array struct {
	popCount  int32
	capacity  int32
	pushCount int32
	memberss  [][unitSize]interface{}
	mtx       sync.Mutex
}

func (a *Array) ConvertIndex(index int32) int32 {
	index = index - (a.popCount / unitSize * unitSize)
	return index
}

func (a *Array) Members() [][unitSize]interface{} {
	return a.memberss
}

func (a *Array) size() {
	fmt.Println("capacity:", a.capacity, len(a.memberss)*unitSize)
}

func (a *Array) donePlayers() int32 {
	return a.popCount
}

func (a *Array) allPlayers() int32 {
	return a.pushCount
}

func (a *Array) pop() {
	a.mtx.Lock()
	defer a.mtx.Unlock()
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
	a.pop()
}

func (a *Array) push(arg interface{}) int32 {
	a.mtx.Lock()
	defer a.mtx.Unlock()
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
	a.memberss[i][j] = arg
	return a.pushCount
}

func (a *Array) Push(arg interface{}) int32 {
	return a.push(arg)
}

func (a *Array) Get(index int32) interface{} {
	a.mtx.Lock()
	defer a.mtx.Unlock()
	index = a.ConvertIndex(index)
	i := index / unitSize
	j := index % unitSize
	return a.memberss[i][j]
}

type Players struct {
	Array
}

func (p *Players) GetToken() {
	if p.popCount == p.pushCount {
		return
	}
	player := p.Get(0).(*UserInfo)
	player.sendMsg(fmt.Sprintf("token %v", player.Index))
	player.Conn.Close()
	p.pop()
}

func (p *Players) notify() {
	p.mtx.Lock()
	defer p.mtx.Unlock()
	for i, players := range p.memberss {
		for j, player := range players {
			if int32(i) < p.pushCount/unitSize || int32(j) < p.pushCount%unitSize {
				member := player.(*UserInfo)
				msg := fmt.Sprintf("当前排在第[%d]位", member.Index-p.popCount)
				fmt.Println(msg)
				member.sendMsg(msg)
			}
		}
	}
}

// var index int32
// var done int32
var players Players

func userHandle(conn net.Conn) {
	userInfo := &UserInfo{
		Conn: conn,
	}
	// atomic.AddInt32(&index, 1)
	userInfo.Index = players.Push(userInfo)
}

// var userQueue = sync.Map[int32]UserInfo{}

func ServerRun() {
	l, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Printf("%v\n", err)
		return
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("accept %v\n", err)
			continue
		}
		fmt.Printf("accept 新用户\n")
		go userHandle(conn)
	}
}

func producer() {
	for {
		players.Push(&UserInfo{})
	}
}

func consumer() {
	for {
		players.GetToken()
	}
}

func printPlayers() {
	for {
		time.Sleep(time.Second * 1)
		fmt.Printf("共接入[%d]玩家\n", players.allPlayers())
		fmt.Printf("待处理玩家[%d]\n", players.allPlayers()-players.donePlayers())
		players.size()
		players.notify()
	}
}

func main() {
	fmt.Println("server running...")
	for i := 0; i < 1; i++ {
		// go producer()
		go consumer()
	}
	go printPlayers()
	ServerRun()

	select {}
}
