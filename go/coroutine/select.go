package main

import (
	"fmt"
	"time"
)

var ch1 = make(chan int, 10)
var ch2 = make(chan int, 10)

func main() {
	var i int
	ch1 <- 1
	ch1 <- 2
	ch1 <- 3
	ch1 <- 4
	ch2 <- 10
	ch2 <- 20
	ch2 <- 30
	ch2 <- 40
	tick := time.NewTicker(time.Second)
	for {
		fmt.Printf("len(ch1) = %d\n", len(ch1))
		fmt.Printf("len(ch2) = %d\n", len(ch2))
		select {
		case i = <-ch1:
			fmt.Printf("ch1 i = %d\n", i)
		case i = <-ch2:
			fmt.Printf("ch2 i = %d\n", i)
		case <-tick.C:
			fmt.Printf("1秒\n")
		}
	}
}
