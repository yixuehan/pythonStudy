package main

import (
	"fmt"
	"time"
)

func main() {
	select {
	case <-time.After(2 * time.Second):
		fmt.Println("time out")
	}
	ch := make(chan int, 1)
	for i := 0; i < 10; i++ {
		select {
		case x := <-ch:
			fmt.Println(x)
		case ch <- i:
		}
	}
}
