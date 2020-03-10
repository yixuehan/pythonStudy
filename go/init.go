package main

import "fmt"

var x = to_var()

func to_var() int {
	return 100
}

func init() {
	fmt.Printf("x = %v\n", x)
	fmt.Println("init")
}

func main() {
	fmt.Printf("x = %v\n", x)
	fmt.Println("main")
}
