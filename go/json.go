package main
import (
    //"fmt"
    "encoding/json"
)

type Person struct {
    Name string `json:"name"`
    Address string `json:"address"`
    Age int `json:"age"`
}

func main() {
    //var ret []byte
    person := Person {
        Name:"xiao m",
        Address:"long yang",
        Age:30,
    }
    for i := 0; i < 1000000; i++ {
        json.Marshal(&person)
    }
    //fmt.Println("ret:", string(ret))

}
