package main

import (
	"bytes"
	"fmt"
	"log"
	"strings"

	"github.com/xwb1989/sqlparser"
)

func subBrackets(str string) string {
	first := strings.Index(str, "(")
	second := strings.LastIndex(str, ")")
	return str[first+1 : second]
}

func parserFrom(sql string) (string, error) {
	stmt, err := sqlparser.Parse(sql)
	if err != nil {
		log.Fatal("sql error:", sql, err)
	}
	var sqlRes string
	switch stmt := stmt.(type) {
	case *sqlparser.Select:
		for _, node := range stmt.From {
			buf := sqlparser.TrackedBuffer{}
			buf.Buffer = &bytes.Buffer{}
			buf.Myprintf("%v", node)
			tableName := fmt.Sprintf("%v", buf)

			tableName = strings.Trim(tableName, " ")
			fmt.Println("tablename:", tableName)
			if strings.Count(tableName, " ") > 0 {
				parserFrom(subBrackets(tableName))
			} else {
				fmt.Printf("%s ", tableName)
			}
		}
	case *sqlparser.Insert:
		fmt.Println("insert")
	}
	return sqlRes, nil
}

func main() {
	sql := `select a.i, a.j, b.m, b.n
		    from (select i, j, id from testa) as a,
			     (select m, n, id from testb) as b
			 where a.id = b.id
          `

	sql = fmt.Sprintf("select i, j, m, n from (%v) as c ", sql)
	sql = `SELECT *
			FROM t_project_job a inner join t_project_project b
			on a.project_id = b.project_id`
	fmt.Println(sql)
	parserFrom(sql)
	fmt.Println()
}
