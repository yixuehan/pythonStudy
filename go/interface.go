package main

import "fmt"

type I1 interface {
	func1()
	func2()
}

type I2 interface {
	func1()
	func2()
}

type S1 struct{}

func (this *S1) func1() {
	fmt.Println("s1...func1")
}

func (this *S1) func2() {
	fmt.Println("s1...func2")
}

func main() {
	s1 := S1{}
	s1.func1()
}
