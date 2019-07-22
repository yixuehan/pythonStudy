package main

import (
	"errors"
	"fmt"
)

func main() {
	var err error
	err = errors.New("abcdef")
	fmt.Println(err.Error())

}
