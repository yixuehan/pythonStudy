package main

import (
	"fmt"
	"time"
)

func main() {
	l, _ := time.LoadLocation("Asia/Chongqing")
	tm := time.Unix(1550827620, 0).In(l)
	fmt.Println(tm)
	tm = time.Unix(1550571000, 0).In(l)
	fmt.Println(tm)
	tm = time.Unix(1550484300, 0).In(l)
	fmt.Println(tm)

}
