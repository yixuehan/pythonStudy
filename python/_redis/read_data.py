#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import redis
import json

conn = redis.StrictRedis(host="10.16.33.25", port=6379)
data = conn.get("robots:device_status_527")
data = json.loads(data)
# print(data)
speed = data["Status"]["Speed"]
print(speed)
print("%.2f" % speed)
speed = speed + 1
print(speed)
