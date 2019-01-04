#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import mako, template
from mako.runtime import Context
from io import StringIO
import io

class Object:
    def __init__(self):
        self.class_name = "object"

obj = Object()

context = {'someval':['abc', 'bcd'],
            'obj':obj,
            }
context2 = {'someval2':['abc2', 'bcd2']}
name = 'define name'
print(template.Template(filename = "./client.mako").render(name = name, **context, **context2))
#print(template.Template(filename = "./client.mako").render()
print(template.Template(filename = "./test.mako").render())
