#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from enum import Enum

Color = Enum("Color", "R G B")

# class Color(Enum):
#     R = "Red"
#     G = "Green"
#     B = "Blue"


print(Color.R)
print(Color.G)
print(Color.B)
C = Color.R
print(C in Color)


# class Attr:
#     def __getattr__(self, name):
#         return name
# 
#     def __getattribute__(self, name):
#         return name
# 
# 
# a = Attr
# a.Dog
# a.Pig
# a.Hello
