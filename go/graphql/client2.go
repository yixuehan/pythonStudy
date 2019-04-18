package main

import (
	"context"
	"fmt"
	"log"

	"github.com/machinebox/graphql"
)

type ResponseStruct struct {
	Data_Active struct {
		Mid  int32
		Low  int32
		High int32
	}
}

// create a client (safe to share across requests)
func main() {
	client := graphql.NewClient("http://localhost:40011/graphql")

	// make a request
	req := graphql.NewRequest(`
    query {
		data_active{
			mid
			high
			low
		}
    }
`)

	// set any variables
	//req.Var("key", "value")

	// set header fields
	req.Header.Set("Cache-Control", "no-cache")

	// define a Context for the request
	ctx := context.Background()

	// run it and capture the response
	var respData ResponseStruct
	if err := client.Run(ctx, req, &respData); err != nil {
		log.Fatal(err)
	}
	fmt.Println(respData.Data_Active.Mid)
	fmt.Println(respData.Data_Active.High)
}
