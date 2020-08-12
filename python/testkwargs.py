#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def func1(a, b, **kwargs):
    print(a, b)


args = {'a': 10, 'b': 20}

# func1(a=1, b=2, **args)
func1(**args)


def func2(*args):
    for arg in args:
        print(arg)


func2('a', 'b', 'c')
