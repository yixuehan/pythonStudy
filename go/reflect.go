package main

import (
	"fmt"
	"reflect"
)

type MyFloat float64

func main() {
	var x MyFloat = 3.4
	fmt.Println("type:", reflect.TypeOf(x))
	fmt.Println("value:", reflect.ValueOf(x))
}
