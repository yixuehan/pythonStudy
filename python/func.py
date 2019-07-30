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


def my_add2(x, y, z):
    return x + y + z


print(my_add(1, 2, 3, 7, 9))
l2 = [10, 11, 13]
print(my_add2(*l2))
