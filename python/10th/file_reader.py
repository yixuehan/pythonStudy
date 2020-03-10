#!/usr/bin/env python3
# -*- coding: utf-8 -*-

filename = 'pi.txt'

with open(filename) as file_object:
    for line in file_object:
        print(line.rstrip())
    print("--------------------")
    contents = file_object.read()
    print(contents)
