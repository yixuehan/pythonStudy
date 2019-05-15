package main

import (
	"encoding/json"
	"fmt"
	"os"
	"strconv"
	//"github.com/buger/jsonparser"
)

// Person ...
type Person struct {
	Name    string `json:"name"`
	Address string `json:"address"`
	Age     int    `json:"age"`
}

type Person2 struct {
	*Person
	Hight int `json:"hight"`
}

type Person3 struct {
	Hight int `json:"hight"`
	Body  interface{}
}

type jsonMap struct {
	JobID     string `json:"jobId"`
	JobStatus string `json:"jobStatus"`
	DataMsg   struct {
		ResultSize  string                         `json:"resultSize"`
		ColumnsInfo map[string](map[string]string) `json:"cloumnsInfo"`
	} `json:"dataMsg"`
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

	str = `{"jobId":"job5hhr3ysff0a01","jobStatus":"END_OF_RUN","dataMsg":{"resultSize":"20","cloumnsInfo":{"0":{"tag_id":"string"},"1":{"1st_class":"string"},"2":{"2nd_class":"string"},"3":{"3rd_class":"string"},"4":{"4th_class":"string"},"5":{"5th_class":"string"}}}}`
	data := []byte(str)
	//fmt.Println(jsonparser.Get(data, "dataMsg", "columnsInfo", "0"))
	var j jsonMap
	json.Unmarshal(data, &j)
	i := 0
	for v, ok := j.DataMsg.ColumnsInfo[strconv.Itoa(i)]; ok; v, ok = j.DataMsg.ColumnsInfo[strconv.Itoa(i)] {
		for f, t := range v {
			fmt.Println(f, t)
		}
		i++
	}
	var person Person2
	person.Person = &Person{}
	person.Age = 100
	bufs, err := json.Marshal(person)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(string(bufs))
	var p3 Person3
	json.Unmarshal(bufs, &p3)
	fmt.Println(p3)
	var persons [2]Person
	persons[0].Age = 10
	persons[1].Age = 20
	bufs, err = json.Marshal(persons)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(string(bufs))

	// var p Person
	// json.Unmarshal(p3.Body.([]byte), &p)
	// fmt.Println(p)
	//for _, v := range j.DataMsg.ColumnsInfo {
	//	for f, t := range v {
	//		fmt.Println(f, t)
	//	}
	//}
}
