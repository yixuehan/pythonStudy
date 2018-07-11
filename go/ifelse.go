package main

import "fmt"

func foo( x int ) int {
    fmt.Println("foo")
    if x < 2 {
        return 1
    } else {
        return 2
    }
}

func main(){
    foo(10)
}
