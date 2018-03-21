#!/usr/bin/env python

import ctypes  
ll = ctypes.cdll.LoadLibrary   
lib = ll("./libpycall.so")    
res = lib.foo(1, 3)  
print "res", res
print '***finish***'  
