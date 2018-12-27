package main

import (
	"encoding/json"
	"fmt"
)

// Person ...
type Person struct {
	Name    string `json:"name"`
	Address string `json:"address"`
	Age     int    `json:"age"`
}

type jsonMap struct {
	ServiceName string `json:service_name`
}

func main() {
	//var ret []byte
	str := `{
	"service_name":"create_job",
    "algorithm_id": "alg123",
    "job_type":"CALCULATE",
    "worktable_name":"test table",
    "job_description":"test",
    "platform_throw_in":"zhiziyun",
    "time_throw_in":"4324324",
    "download_type":"REPORT",
    "interface_type":"BOOLEAN"
    }`
	j := jsonMap{}
	err := json.Unmarshal([]byte(str), &j)
	fmt.Println(err)
	fmt.Println(j.ServiceName)
}
