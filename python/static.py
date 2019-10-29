#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class A:
    @staticmethod
    def printObj():
        print("obj a")

    def __init__(self):
        pass

    def fn(self):
        self.printObj()


class B(A):
    def __init__(self):
        pass

    @staticmethod
    def printObj():
        print("obj b")


b = B()
b.fn()
