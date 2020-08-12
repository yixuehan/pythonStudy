package main

import "fmt"

type A struct {
}

func (a *A) Bool() bool {
	return true
}

func (a *A) Boolean() bool {
	return true
}

func main() {
	a := &A{}
	if bool(a) {
		fmt.Println("true")
	}
}
