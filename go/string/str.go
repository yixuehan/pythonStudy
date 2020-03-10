package main

import "fmt"

func main() {
	a := "abc"
	b := a
	fmt.Printf("%p:%p\n", &a, &b)
	fmt.Printf("%v:%v\n", a, b)
	a = a[1:]
	// a[0] = byte(100)
	fmt.Printf("%p:%p\n", &a, &b)
	fmt.Printf("%v:%v\n", a, b)
}
