#!/usr/bin/python

str = "this is really a string example is....wow!!!"
substr = "is"

print( str.rfind(substr, 10))
print( str.rfind(substr, 0, 10))
print( str.rfind(substr, 10, 0))

print( str.find(substr))
print( str.find(substr, 0, 10))
print( str.find(substr, 10, 0))

