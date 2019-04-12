#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class Iter():
    def __init__(self):
        self.nums = [1, 2, 3, 4, 5]

    def __iter__(self):
        return self

    def items(self):
        for i in self.nums:
            yield i


it = Iter()
for i in it.items():
    print(i)
for i in it.items():
    print(i)
