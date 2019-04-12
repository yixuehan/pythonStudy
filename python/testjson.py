#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json


a = json.loads('''
{
 "code" : 0,
 "message" : "",
 "data" :
 [
  {
   "name": "汽车",
   "value": {
    "count": 100,
    "trade":40
   }
  },
  {
   "name": "金融",
   "value": {
    "count": 100,
    "trade":40
   }
  }
 ]
}
''')

print(a)
