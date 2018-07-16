package main

import (
       "fmt"
)

func main()  {

       var whatever  [5]struct{}

       for i := range whatever {

              fmt.Println(i)
       } //part 1

       for i := range whatever {

              defer func() { fmt.Println(i)}()
       } //part 2


       for i := range whatever {

              defer func(n int) { fmt.Println(n)}(i)
       } //part 3
}
