package main

import "fmt"

type A struct {
	X int
	Y string
}

func (a *A) String() string {
	return fmt.Sprintf("X[%v] Y[%v]", a.X, a.Y)
}

func main() {
	a := A{}
	fmt.Printf("%v\n", a.String())
}
