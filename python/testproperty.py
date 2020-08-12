#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class A:
    def __init__(self):
        self.__name = None

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    def print_name(self):
        print(self.__name)


if __name__ == '__main__':
    a = A()

    a.name = 'abc'
    print(a.name)
    a.print_name()
