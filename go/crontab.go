package main

import (
	"fmt"
	"time"

	"github.com/robfig/cron"
)

func main() {
	ch := make(chan int)
	c1 := cron.New()
	c2 := cron.New()
	funcSecond := func() {
		fmt.Println("every second")
	}
	func2Second := func() {
		fmt.Println("every 2 seoncd")
	}
	c1.AddFunc("* * * * * *", funcSecond)
	c2.AddFunc("*/2 * * * * *", func2Second)
	c1.Start()
	c2.Start()

	//time.Sleep(time.Second * 5)
	tm := time.Now()
	for i := 0; i < 10; i++ {
		sche, _ := cron.Parse("*/3 * * * * *")
		tm = sche.Next(tm)
		fmt.Println("next time:", tm)
	}

	c1.Stop()

	<-ch
}
