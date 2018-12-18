package main

import "fmt"
import "regexp"

func main() {
	//match, _ := regexp.MatchString("[\u4e00-\u9fa5]", "你好abc")
	r, _ := regexp.Compile("[\u4e00-\u9fa5]")
	res := r.FindAllString("你好abc", -1)
	fmt.Println(res, len(res))
	fmt.Println()
}
