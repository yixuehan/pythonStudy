package main

import (
	"fmt"
	"net"
	"os"
	"time"
	"token/define"
)

type TokenServer struct {
	players         define.Queue
	playerChan      chan *define.PlayerInfo
	playerTokenChan chan string
	// producerToken   chan int32
	tokenNum       int32
	ticker         *time.Ticker
	playerLocation int32
}

// 通知所有玩家当前的排除位置
func (t *TokenServer) notifyAll() {
	var i int32
	for i = 0; i < t.players.Size(); i++ {
		ele := t.players.At(i)
		if ele == nil {
			fmt.Printf("players[%d], curr[%d]\n", t.players.Size(), i)
			break
		}
		player := ele.(*define.PlayerInfo)
		player.SendMsg(fmt.Sprintf("玩家[%d]当前位置[%d]", player.Location, i+1))
	}
}

// 模拟获取token的过程
func (t *TokenServer) getToken() {
	//fmt.Printf("players[%d] tokens[%d]\n", t.players.Size(), int32(len(t.playerTokenChan)))
	for {
		// time.Sleep(time.Millisecond * 10)
		if t.players.Size() > int32(len(t.playerTokenChan)) {
			//fmt.Printf("for players[%d] tokens[%d]\n", t.players.Size(), int32(len(t.playerTokenChan)))
			// 实际可能是向token服务器请求
			t.playerTokenChan <- fmt.Sprintf("token:%v", t.tokenNum)
			t.tokenNum++
		} else {
			// fmt.Printf("token已经满足，暂不生产\n")
			time.Sleep(time.Second * 1)
		}
	}
}

func (t *TokenServer) playerQueuing() {
	var p, player *define.PlayerInfo
	var ele define.Element
	var token string
	// var tokenNum int32
	for {
		select {
		case p = <-t.playerChan:
			//fmt.Printf("增加新用户\n")
			p.Location = t.playerLocation
			t.playerLocation++
			t.players.Push(p)
		case token = <-t.playerTokenChan:
			ele = t.players.Pop()
			if ele != nil {
				player = ele.(*define.PlayerInfo)
				//fmt.Printf("有用户获取token")
				player.SendMsg(token)
				player.Conn.Close()
			} else {
				//fmt.Printf("无等待玩家\n")
				time.Sleep(time.Second * 1)
			}
		case <-t.ticker.C:
			t.notifyAll()
		}
		//fmt.Printf("队列处理...\n")
	}
}

func (t *TokenServer) Init() {
	t.ticker = time.NewTicker(time.Second)
	t.players = new(define.PlayerQueue)
	t.playerChan = make(chan *define.PlayerInfo, 10000)
	t.playerTokenChan = make(chan string, 10000)
	// t.producerToken = make(chan int32, 1000)
	go t.playerQueuing()
	go t.getToken()
}

func (t *TokenServer) Run(addr string) {
	t.Init()
	l, err := net.Listen("tcp", addr)
	if err != nil {
		fmt.Printf("%v\n", err)
		return
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("accept 失败:%v, 当前用户数量[%d]\n", err, t.players.Size())
			continue
		}
		//fmt.Printf("accept 新用户\n")
		// go func(conn net.Conn) {
		// 排列处理，如有需要可改为epoll模式，设置keep-alive
		t.playerChan <- &define.PlayerInfo{
			Conn: conn,
		}
		// }(conn)
	}
}

func main() {
	fmt.Printf("server running... pid[%v]\n", os.Getpid())
	s := TokenServer{}
	s.Run(":8888")
}
