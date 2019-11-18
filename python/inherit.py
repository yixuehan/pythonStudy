#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class A:
    def __init__(self, x):
        self.__x = x
        self.__a = 'a'

    def print(self):
        print('A:', self.__x)

    def foo(self):
        self.print()

    @property
    def a(self):
        return self.__a


class B(A):
    def __init__(self, x):
        A.__init__(self, x)
        self.__x = x

    def print(self):
        print('B:', self.__x, self.__a)


# class C(A, B):
#     def print(self):
#         self.B.print(self)


if __name__ == '__main__':
    b = B(10)
    b.foo()
