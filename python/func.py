#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def add_end(L=None):
    if L is None:
        L = []
    L.append('end')
    return L


print(add_end())
print(add_end())
print(add_end())
print(add_end())


def my_add(*nums):
    res = 0
    for num in nums:
        res += num
    return res


print(my_add(1, 2, 3, 7, 9))
