package main

import (
	"encoding/json"
	"time"

	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
	"gopkg.in/natefinch/lumberjack.v2"
)

var logger *zap.Logger

func SetLogger(l *zap.Logger) {
	logger = l
	logger.Named("history")
}

func LogInOtherFile() {
	logger.Info("log in demo", zap.String("user", "cc"))
}

type TestJson struct {
	A string
	B int
}

func main() {
	rawJSON := []byte(`{
	  "level": "debug",
	  "encoding": "json",
	  "outputPaths": ["stdout", "./demo.log"],
	  "errorOutputPaths": ["stderr"],
	  "initialFields": {},
	  "encoderConfig": {
	    "messageKey": "message",
	    "levelKey": "level",
	    "levelEncoder": "lowercase"
	  }
	}`)

	var cfg zap.Config
	if err := json.Unmarshal(rawJSON, &cfg); err != nil {
		panic(err)
	}
	cfg.EncoderConfig.EncodeTime = zapcore.ISO8601TimeEncoder
	cfg.EncoderConfig.TimeKey = "ts"
	var rotate lumberjack.Logger
	rotate.Filename = "project.log"
	rotate.LocalTime = true
	zapcore.AddSync(&rotate)
	logger, err := cfg.Build()
	if err != nil {
		panic(err)
	}
	defer logger.Sync()

	logger.Info("logger construction succeeded")
	var testJson TestJson
	testJson.A = "testA"
	testJson.B = 100

	var byteRes []byte
	byteRes, err = json.Marshal(&testJson)
	logger.Info(string(byteRes))
	if err != nil {
		panic(err)
	}
	logger.Operate(string(byteRes))
	logger.Info("msg", zap.String("operate", string(byteRes)))
	SetLogger(logger)
	LogInOtherFile()
	time.Sleep(time.Second * 10)
}
