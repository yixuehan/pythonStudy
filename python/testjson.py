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

# print(a)


class Student:
    def __init__(self):
        self.name = ""
        self.age = 15
        self.sex = "男"
        self.email = "abc@162.com"
        self.address = "address test"
        self.next = None

    def __str__(self):
        return "%s %s %s %s %s %s" % (self.name, self.age, self.sex, self.email, self.address, self.next)


student = Student()
student.next = Student().__dict__
print(student.__dict__)
student2 = Student()
student2.__dict__ = student.__dict__
print(student2)
