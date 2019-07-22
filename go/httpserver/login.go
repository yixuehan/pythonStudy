package main

import (
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
)

type Login struct {
	User     string `form:"user" json:"user" xml:"user" binding:"required"`
	Password string `form:"password" json:"password" xml:"password" binding:"required"`
}

type resp struct {
	Status string `json:"status"`
}

func main() {
	router := gin.Default()
	router.POST("/login", func(c *gin.Context) {
		var json1 Login
		var json2 Login
		if err := c.ShouldBind(&json1); err != nil {
			fmt.Println("json1:", err)
		}
		//json2.User = json1.User

		if err := c.ShouldBindJSON(&json2); err != nil {
			fmt.Println("json2:", err)
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}

		if json2.User != "manu" || json2.Password != "123" {
			c.JSON(http.StatusUnauthorized, gin.H{"status": "unauthorized"})
			return
		}
		r := resp{}
		r.Status = "You are logged in hahaha"
		c.JSON(http.StatusOK, &r)
	})

	router.Run()
}
