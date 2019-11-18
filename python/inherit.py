#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class A:
    def __init__(self, x):
        self.__x = x
        self.__a = 'a'

    def my_print(self):
        print('A:', self.__x)

    def foo(self):
        self.my_print()
        A.my_print(self)

    @property
    def a(self):
        return self.__a


class B(A):
    def __init__(self, x):
        A.__init__(self, x)
        self.__x = x

    def my_print(self):
        print('B:', self.__x, self.a)

    def foo(self):
        A.foo(self)


# class C(A, B):
#     def print(self):
#         self.B.print(self)


if __name__ == '__main__':
    b = B(10)
    b.foo()
