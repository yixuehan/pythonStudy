package main

// import "github.com/gin-gonic/gin"
import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"
)

type Login struct {
	User     string `form:"user" json:"user" xml:"user" binding:"required"`
	Password string `form:"password" json:"password" xml:"password" binding:"required"`
}

type resp struct {
	Status string `json:"status"`
}

func main() {
	client := http.Client{}
	var login Login
	login.User = "manu"
	login.Password = "123"
	buf, err := json.Marshal(&login)
	if err != nil {
		log.Fatal(err)
	}

	request, err := http.NewRequest("POST", "http://localhost:8080/login", strings.NewReader(string(buf)))
	if err != nil {
		log.Fatal(err)
	}
	request.Header.Set("Content-Type", "application/x-www-form-urlencoded")
	respond, err := client.Do(request)
	if err != nil {
		log.Fatal(err)
	}
	defer respond.Body.Close()
	body, err := ioutil.ReadAll(respond.Body)
	var r resp
	json.Unmarshal(body, &r)
	fmt.Println(r)
}
