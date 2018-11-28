package main

import "fmt"

func modify(arr []int) {
	arr[0] = 100
	fmt.Println("len:", len(arr))
	fmt.Println("modify:", arr)
}

func main() {
	var arr [10]int = [10]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
	var slice_arr []int = arr[:5]
	modify(slice_arr)
	fmt.Println("after modify:", arr)
	fmt.Println("after modify:", slice_arr)
}
