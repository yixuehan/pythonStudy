package main

import (
	"fmt"
	"net/http"
	"os"
	"time"

	"github.com/julienschmidt/httprouter"
)

func addData(w http.ResponseWriter, r *http.Request, p httprouter.Params) {
	// buf, err := ioutil.ReadAll(r.Body)
	// if err != nil {
	// 	fmt.Fprintf(w, err.Error())
	// }
	// n := len(buf)
	fmt.Println(r.URL.Query())
	// fmt.Println("buf:", string(buf))
	// fmt.Println("len:", n)
	r.ParseForm()
	fmt.Println("header abc:", r.Header.Get("abc"))

	for k, v := range r.Form {
		fmt.Println("form:", k, v)
	}

	// multipart.Form

	r.ParseMultipartForm(4096)
	if r.MultipartForm != nil {
		for k, v := range r.MultipartForm.Value {
			fmt.Println("multipart:", k, v)
		}
	}

	fmt.Fprintf(w, "ok")
}

func hello(w http.ResponseWriter, r *http.Request, p httprouter.Params) {
	fmt.Println(p.ByName("name"))
	fmt.Fprintf(w, "hello")
}

func main() {
	router := httprouter.New()
	router.POST("/hello", hello)
	router.POST("/addData", addData)
	server := http.Server{
		ReadTimeout: 3 * time.Second,
		Addr:        ":8080",
		Handler:     router,
	}
	if err := server.ListenAndServe(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
