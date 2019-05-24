#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import json
# import copy


class B:
    def __init__(self):
        self.a = '123'
        self.b = 456
        pass

    def to_json(self):
        m = {}
        m['a'] = self.a
        m['b'] = self.b
        return json.dumps(m)


class A:
    def __init__(self, name):
        self.__name = name
        self.__bs = [B() for _ in range(10)]

    def __eq__(self, o):
        print("__eq__")
        return self.__name == o.__name

    def to_json(self):
        m = {}
        m['name'] = self.__name
        m['bs'] = []
        for i in range(0, len(self.__bs)):
            m['bs'].append(self.__bs[i].to_json())
        return json.dumps(m)


if __name__ == '__main__':
    a1 = A("name1")
    a2 = A("name2")

    strs = ["a", 'b', 'c', 'd', 'e', 'f']
    lista = [A(s) for s in strs]
    if a1 in lista:
        pass
        # print("true")

    print(a1.to_json())
