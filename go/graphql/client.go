package main

import "fmt"
import "github.com/shurcooL/graphql"
import "net/http"
import "context"

type ResultCount struct {
	Rows    int64 `graphql:"numRows"`
	Columns int64 `graphql:"numColumns"`
}

type QueryProjectInfoList struct {
	Job struct {
		AlgoResult  string      `graphql:"algoResult"`
		ResultCount ResultCount `graphql:"resultCount"`
	} `graphql:"job(jobId:$job_id)"`
}

func main() {

	client := http.Client{}
	graphqlClient := graphql.NewClient("http://192.168.150.221:15000/private/graphql", &client)
	query := QueryProjectInfoList{}
	variables := map[string]interface{}{
		"job_id": graphql.String("job5hcl6d1mi0a0v"),
	}
	err := graphqlClient.Query(context.Background(), &query, variables)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(query)
	}
	err = graphqlClient.Query(context.Background(), &query, variables)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(query)
	}
	//'{"query": "{projectInfoList{projectID}}"}' \
}
