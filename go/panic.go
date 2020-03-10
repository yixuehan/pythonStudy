package main

import "fmt"

func fn() {
	defer func() {
		if p := recover(); p != nil {
			fmt.Printf("internal error: %v\n", p)
		}
	}()
	panic("abc")
}

func main() {
	fn()
}
