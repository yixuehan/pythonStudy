package main
import (
    "fmt"
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
    var ret []byte
    for i := 0; i < 1; i++ {
        ret, _ = json.Marshal(&person)
    }
    fmt.Println("ret:", string(ret))
    person.Address = string(ret)
    ret, _ = json.Marshal(&person)
    fmt.Println("ret:", string(ret))

}
