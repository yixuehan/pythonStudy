package main

import "fmt"

func main() {
	var buf []byte
	buf1 := []byte(fmt.Sprintf("%0*v", 8, 1024))
	buf2 := []byte(fmt.Sprintf("%0*v", 7, 1024))
	buf = append(buf1, buf2...)
	fmt.Printf("%v:[%s]\n", len(buf), string(buf))
}
