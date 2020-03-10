package main

import (
	"encoding/json"
	"fmt"
)

type A struct {
	S1 string `json:"s1"`
	S2 string `json:"s2"`
}

type B struct {
	A
	S3 string `json:"s3"`
	S4 string `json:"s4"`
}

func main() {
	var a B
	buf, _ := json.Marshal(&a)
	fmt.Println(string(buf))

	buf = []byte(`{"s3":"s3","s4":"s4"}`)

	json.Unmarshal(buf, &a)
	fmt.Println(a)

}
