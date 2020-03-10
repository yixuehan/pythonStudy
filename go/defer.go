package main

import (
	"fmt"
)

func main() {
	x := 2
	defer func() {
		fmt.Println(x * x * x)
	}()
	x = 3
}
