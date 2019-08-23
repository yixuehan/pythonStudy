#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class attr:
    __type_list = ('req', 'resp', 'enum', 'api', 'config')

    def __init__(self, _type):
        assert _type in Attr.__type_list
        self.__type = _type

    @property
    def type(self):
        return self.__type


class Attr(attr):
    def __init__(self, name):
        attr.__init__(self, name)

    def __getattr__(self, name):
        return name == ('is_' + attr.__getattribute__(self, "type"))


a = Attr('req')
print(a.is_req)
print(a.is_resp)
