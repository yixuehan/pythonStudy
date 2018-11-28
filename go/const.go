package main

import "fmt"

const (
	Sunday = iota
	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
	numberOfDays // 这个常量没有导出
)

func main() {
	const a int = 10
	const (
		H = iota
		I
		J
		b = 10
		c = 20
	)
	fmt.Println(Sunday, numberOfDays)
	fmt.Println("a = %d, b = %d, c = %d\n", a, b, c)
}
