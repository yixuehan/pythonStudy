package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println(time.Time.Format(time.Now(), "20060102"))
}
