package main

import (
	"log"
	"net/http"

	graphql "github.com/graph-gophers/graphql-go"
	"github.com/graph-gophers/graphql-go/relay"
)

type query struct{}

func (_ *query) Hello() string  { return "Hello, world!" }
func (_ *query) Hello2() string { return "Hello2, world!" }

func main() {
	s := `
                schema {
                        query: Query
                }
                type Query {
                        hello: String!
                        hello2: String!
                }
        `
	schema := graphql.MustParseSchema(s, &query{})
	http.Handle("/query", &relay.Handler{Schema: schema})
	log.Fatal(http.ListenAndServe(":8080", nil))
}
