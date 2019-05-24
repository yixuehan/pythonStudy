package main

import "github.com/gin-gonic/gin"
import "net/http"

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
		var json Login
		if err := c.ShouldBindJSON(&json); err != nil {
			if err = c.ShouldBind(&json); err != nil {
				c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
				return
			}
		}

		if json.User != "manu" || json.Password != "123" {
			c.JSON(http.StatusUnauthorized, gin.H{"status": "unauthorized"})
			return
		}
		r := resp{}
		r.Status = "You are logged in hahaha"
		c.JSON(http.StatusOK, &r)
	})

	router.Run()
}
