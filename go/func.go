package main

import (
    "fmt"
    "./pkg"

)

func delta(old, new int) int {
    return new - old
}

func main() {
    pack2.Foo()
    fmt.Println(delta(10, 20))
}
