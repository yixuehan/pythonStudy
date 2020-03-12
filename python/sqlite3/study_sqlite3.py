#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3

conn = sqlite3.connect("test.db")

cursor = conn.cursor()

sql = "create table user(id varchar(20) primary key, name varchar(20))"

cursor.execute(sql)

conn.close()
