package main

import (
	"fmt"
	"runtime"
)

func call(skip int) {
	pc, file, line, ok := runtime.Caller(skip)
	fmt.Println(pc, file, line, ok)
}

func main() {
	call(1)
}
