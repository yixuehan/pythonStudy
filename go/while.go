package main

func main() {
	c := make(chan int)
	go func() {
		for true {
		}
	}()
	<-c
}
