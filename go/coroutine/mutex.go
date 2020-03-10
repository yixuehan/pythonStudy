package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

var once sync.Once

func doOnce() {
	fmt.Println("init")
}

var wg sync.WaitGroup

func main() {
	once.Do(doOnce)
	once.Do(doOnce)
	once.Do(doOnce)
	// wg.Add(coroutineCount)
	for i := 0; i < coroutineCount; i++ {
		wg.Add(1)
		go AddOne()
	}
	wg.Wait()
	fmt.Println(g_count)
}

var g_count int32 = 0
var coroutineCount = 10000

func AddOne() {
	for i := 0; i < 10000; i++ {
		atomic.AddInt32(&g_count, 1)
		// g_count++
	}
	wg.Done()
}
