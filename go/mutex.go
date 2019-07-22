package main

import (
	"fmt"
	"sync"
)

var once sync.Once

func doOnce() {
	fmt.Println("init")
}

func main() {
	once.Do(doOnce)
	once.Do(doOnce)
	once.Do(doOnce)
}
