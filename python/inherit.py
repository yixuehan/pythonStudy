#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class A:
    def __init__(self, x):
        self.__x = x

    def print(self):
        print('A:', self.__x)


class B:
    def __init__(self, x):
        self.__x = x

    def print(self):
        print('B:', self.__x)


class C(A, B):
    def print(self):
        self.B.print(self)


if __name__ == '__main__':
    c = C(10)
    c.print()
