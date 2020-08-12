package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"time"

	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
	"github.com/shirou/gopsutil/cpu"
)

func main() {
	//初始化日志服务两种方式
	//logger := log.New(os.Stdout, "[Memory]", log.Lshortfile | log.Ldate | log.Ltime)
	logName := "prometheus-cpu-logs.log"
	logfile, err := os.Create(logName)
	if err != nil {
		log.Fatalln("open log file error.")
	}
	defer logfile.Close()
	logger := log.New(logfile, "[Test-logs]\t", log.Ldate|log.Ltime)
	logger.Println("\tA test message.")

	//初始一个http handler
	http.Handle("/metrics", promhttp.Handler())

	//初始化一个容器
	diskPercent := prometheus.NewGaugeVec(prometheus.GaugeOpts{
		Name: "cpu_percent",
		Help: "cpu use percent",
	},
		[]string{"percent"},
	)
	prometheus.MustRegister(diskPercent)

	// 启动web服务，监听1010端口
	go func() {
		logger.Println("ListenAndServe at:localhost:8081")
		err := http.ListenAndServe("localhost:8081", nil)
		if err != nil {
			logger.Fatal("ListenAndServe: ", err)
		}
	}()

	//收集内存使用的百分比
	for {
		logger.Println("start collect cpu used percent!")

		// usedPercent, err := cpu.Percent(time.Second, false)
		usedPercent, err := cpu.Percent(time.Second, true)
		fmt.Printf("percent:%v\n", usedPercent)
		if err != nil {
			logger.Println("get cpu use percent error:%s", err)
		}
		usedPercent2 := fmt.Sprintf("%v", usedPercent)
		usedPercent2 = usedPercent2[1 : len(usedPercent2)-1]
		logger.Println("get cpu use percent:", usedPercent2)
		// diskPercent.WithLabelValues("usedcpu").Set(usedPercent2)
		diskPercent.WithLabelValues("usedcpu").Set(usedPercent[0])
		time.Sleep(time.Second * 2)
	}
}
