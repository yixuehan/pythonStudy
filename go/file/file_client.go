package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"mime/multipart"
	"net/http"
	"os"
)

func postFile(filename string, targetURL string) error {
	bodyBuf := &bytes.Buffer{}
	bodyWriter := multipart.NewWriter(bodyBuf)
	fileWriter, err := bodyWriter.CreateFormFile("uploadfile", filename)
	if err != nil {
		log.Fatal(err)
	}
	fh, err := os.Open(filename)
	if err != nil {
		log.Fatal(err)
	}
	_, err = io.Copy(fileWriter, fh)
	if err != nil {
		log.Fatal(err)
	}
	contentType := bodyWriter.FormDataContentType()
	bodyWriter.Close()
	resp, err := http.Post(targetURL, contentType, bodyBuf)
	if err != nil {
		log.Fatal(err)
	}
	defer resp.Body.Close()
	resp_body, err := ioutil.ReadAll(resp.Body)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(resp.Status)
	fmt.Println(string(resp_body))
	return nil
}

func getFile(targetURL string) error {
	resp, err := http.Get(targetURL)
	if err != nil {
		log.Fatal(err)
	}
	defer resp.Body.Close()
	resp_body, err := ioutil.ReadAll(resp.Body)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(resp.Status)
	fmt.Println(string(resp_body))
	return nil
}

func main() {
	target_url := "http://localhost:9090/upload"
	filename := "./mysql++-3.2.4.tar.gz"
	postFile(filename, target_url)
	getFile(target_url)
}
