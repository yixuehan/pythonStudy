package main

import "fmt"

func changeMap(nameAge map[string]int) {
	nameAge = make(map[string]int)
	nameAge["newname"] = 30
}

func main() {
	nameAge := make(map[string]int)
	nameAge["xiaoming"] = 19
	nameAge["xiaozhang"] = 20
	changeMap(nameAge)
	fmt.Println(nameAge)
	fmt.Println("nameAge:", type(nameAge["notexists"]))
}
