package main

import "fmt"

func delta(old, new int) int {
    return new - old
}

func main() {
    fmt.Println(delta(10, 20))
}
