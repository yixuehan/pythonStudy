package main

import (
	"./pkg"
	"fmt"
)

func delta(old, new int) int {
	return new - old
}

func multiret()(int, int) {
	return 1, 2
}

func main() {
	pack2.Foo()
	fmt.Println(delta(10, 20))
	a := multiret()
	fmt.Println(a)
}
