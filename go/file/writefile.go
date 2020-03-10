package main

import "os"

func main() {
	file, _ := os.OpenFile("write.txt", os.O_CREATE|os.O_WRONLY, 0644)
	// file.WriteString("1wopfjpwfjipqaofjpowfjpoqjifqewpfjepoqjfpojewofwowjofwpqf")
	file.WriteString("1234")
}
