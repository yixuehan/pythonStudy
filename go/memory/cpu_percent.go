package main

import (
	"fmt"
	"time"

	"github.com/shirou/gopsutil/cpu"
)

func main() {
	c, err := cpu.Info()
	if err != nil {
		fmt.Println("cpu info error")
	}
	for _, ci := range c {
		fmt.Println(ci)
	}

	for {
		parcent, _ := cpu.Percent(time.Second, false)
		str := fmt.Sprintf("%v", parcent)
		str = str[1 : len(str)-1]
		fmt.Printf("percent:%v\n", str)
	}
}
