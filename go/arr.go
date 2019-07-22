package main

import "fmt"

func modify(arr []int) {
	arr[0] = 100
	fmt.Println("len:", len(arr))
	fmt.Println("modify:", arr)
}

func testArr(a interface{}) {
}

func main() {
	var arr [10]int = [10]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
	var arr2 [10]int = [10]int{21, 22, 23, 24, 25, 26, 27, 28, 29, 20}
	var slice_arr []int = arr[:5]
	var slice_arr2 []int = arr2[5:]
	modify(slice_arr)
	modify(slice_arr2)
	fmt.Println("after modify:", arr)
	fmt.Println("after modify:", arr, slice_arr)
	fmt.Println("after modify:", arr2, slice_arr2)
	slice_arr = append(slice_arr, slice_arr2...)
	testArr(slice_arr)
	slice_arr[0] = 11
	slice_arr[4] = 55
	fmt.Println("after modify:", arr, slice_arr)
	fmt.Println("after modify:", arr2, slice_arr2)
	fmt.Println("len:", len(arr[0:10]))
}
