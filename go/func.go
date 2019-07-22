package main

import (
	"fmt"
)

func delta(old, new int) int {
	return new - old
}

func multiret() (int, int) {
	return 1, 2
}

func main() {
	//pack2.Foo()
	//fmt.Println(delta(10, 20))
	//a := multiret()
	//fmt.Println(a)
	var a A
	fmt.Printf("%p\n", &a)
	a.Set(10, 20)
	a.Print()
}

type A struct {
	x int
	y int
}

func (a *A) Print() {
	fmt.Printf("%p\n", a)
	fmt.Println(a.x, a.y)
}

func (a A) Set(x, y int) {
	fmt.Printf("%p\n", &a)
	a.x = x
	a.y = y
}
