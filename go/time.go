package main

import (
	"fmt"
	"os"
	"time"
)

func GetMsSecond() int64 {
	return time.Now().UnixNano() / (1000 * 1000)
}

//获取当前时间的字符串格式
func GetTimeStr() string {
	return time.Now().Format("2006-01-02 15:04:05")
}
func GetTimeInt() int64 {
	return time.Now().Unix()
}
func Time2String(timeUnix int64) string {
	return time.Unix(timeUnix, 0).Format("2006-01-02 15:04:05")
}
func String2Time(formatTimeStr string) int64 {

	// {
	// 	{
	// 		formatTime, _ := time.Parse("2006-01-02 15:04:05", "2019-05-13 18:59:05")
	// 		fmt.Println(formatTime.Unix())
	// 	}
	// 	{
	// 		formatTime, _ := time.Parse("2006-01-02 15:04:05", formatTimeStr)
	// 		fmt.Println(formatTime.Unix())
	// 	}
	// }
	formatTime, _ := time.Parse("2006-01-02 15:04:05", formatTimeStr)
	fmt.Println(formatTime.Unix())
	return formatTime.Unix()
}

func main() {
	// t := time.Time{}
	var t time.Time
	t2 := time.Time{}
	fmt.Println(t == t2)
	fmt.Println(t == time.Time{})
	if t == time.Time{} {
		fmt.Println("true")
	}
	return

	fmt.Println(GetTimeStr())
	fmt.Println(GetTimeInt())
	fmt.Println(Time2String(GetTimeInt()))
	fmt.Println(String2Time(GetTimeStr()))

	{
		formatTime, _ := time.Parse("2006-01-02 15:04:05", "2019-05-13 15:04:05")
		fmt.Println(formatTime.Unix())
	}
	//时间戳转时间字符串 (int64 —>  string)
	var formatTimeStr string
	{
		timeUnix := time.Now().Unix()
		formatTimeStr = time.Unix(timeUnix, 0).Format("2006-01-02 15:04:05")
		fmt.Println("time format:", formatTimeStr)

		formatTime, err := time.Parse("2006-01-02 15:04:05", formatTimeStr)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		fmt.Println(formatTime.Unix())
	}

	//formatTimeStr := GetTimeStr()
	//fmt.Println(formatTimeStr)
	str2 := GetTimeStr()
	//str1 := formatTimeStr
	//fmt.Println(formatTimeStr)
	//fmt.Println(str1)

	//时间字符串转时间(string  —>  Time)
	//formatTimeStr = "2017-04-11 13:33:37"
	//formatTimeStr = "2019-05-13 19:10:49"
	fmt.Println("time format:", formatTimeStr)
	if str2 != formatTimeStr {
		fmt.Printf("not equal[%s][%s]\n", str2, formatTimeStr)
		for _, c := range str2 {
			fmt.Printf("%X ", c)
		}
		fmt.Println()
		for _, c := range formatTimeStr {
			fmt.Printf("%X ", c)
		}
		fmt.Println()
		// fmt.Printf("not equal[%X][%X]\n", str2, formatTimeStr)
	}
	formatTime, err := time.Parse("2006-01-02 15:04:05", formatTimeStr)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(formatTime.Unix())
}
