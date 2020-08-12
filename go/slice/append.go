package main

import "fmt"

func main() {
	arr := [10]int{10, 20, 30}
	fmt.Printf("arr:%v\n", &arr)
	slice := arr[0:2]
	fmt.Printf("slice:%p\n", slice)
	slice = append(slice, 1)
	fmt.Printf("slice:%p\n", slice)
	slice = append(slice, 2)
	fmt.Printf("slice:%p\n", slice)
	slice = append(slice, 3)
	fmt.Printf("slice:%p\n", slice)
	slice = append(slice, 4)
	for i := 0; i < 10000; i++ {
		slice = append(slice, i)
	}
	slice[0] = 101
	fmt.Printf("%v:%v\n", arr[0], slice[0])
}
