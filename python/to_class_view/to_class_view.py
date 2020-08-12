#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os


class Convert:
    def __init__(self):
        self.__private_variable = 'private_variable.txt'
        self.__public_variable = 'public_variable.txt'
        self.__protected_variable = 'protected_variable.txt'
        self.__private_func = 'private_func.txt'
        self.__public_func = 'public_func.txt'
        self.__protected_func = 'protected_func.txt'

    def convert(self):
        self.__convert_private_variable()
        self.__convert_public_variable()
        self.__convert_protected_variable()
        self.__convert_private_func()
        self.__convert_public_func()
        self.__convert_protected_func()

    def __uncomment(self, filename):
        if not os.path.exists(filename):
            return ''
        text = ''
        ret_text = ''
        with open(filename, 'r') as f:
            text = f.read()
        left = text.find("/*")
        right = 0
        # print(text)
        while left >= 0:
            ret_text += text[right:left]
            right = text.find("*/", left + 2)
            # print("%d:%d" % (left, right))
            assert right > 0
            right = right + 2
            left = text.find("/*", right)
        ret_text += text[right:]
        text = ret_text

        left = text.find("//")
        right = 0
        ret_text = ''
        while left >= 0:
            ret_text += text[right:left]
            right = text.find("\n", left + 2)
            assert right > 0
            right = right + 1
            left = text.find("//", right)
        ret_text += text[right:]
        return ret_text

    def __convert_public_func(self):
        self.__convert_func(self.__public_func, '+')

    def __convert_protected_func(self):
        self.__convert_func(self.__protected_func, '#')

    def __convert_private_func(self):
        self.__convert_func(self.__private_func, '-')

    def __convert_func(self, filename, tag):
        lines = []
        # rets = []
        text = self.__uncomment(filename)
        lines = text.split('\n')
        line = ""
        for l in lines:
            line += l.strip()
            if not line:
                continue
            # print("line:", line)
            if line[-1] == ';':
                line = line[:-1]
            else:
                line = line[:-1]
                continue

            # 找到第一个'('和最后一个')'
            left = line.find('(')
            # right = line.find(')')
            func_pos = left - 1
            while func_pos >= 0 and line[func_pos] == ' ':
                func_pos = func_pos - 1
            while func_pos >= 0 and line[func_pos] != ' ':
                func_pos = func_pos - 1
            func_pos = func_pos + 1
            ret_pos = func_pos - 1

            # pos
            while ret_pos >= 0 and line[ret_pos] == ' ':
                ret_pos = ret_pos - 1
            while ret_pos >= 0 and line[ret_pos] != ' ':
                ret_pos = ret_pos - 1
            if ret_pos == -1:
                ret_pos = 0

            ret_type = line[ret_pos:func_pos].rstrip()
            # print("ret_type:", ret_type)

            if not ret_type or ret_type in ['virtual']:
                ret = "%s %s" % (tag, line)
            else:
                func = line[:ret_pos] + line[ret_pos + len(ret_type):]
                ret = "%s %s : %s" % (tag, func, ret_type)
            # rets.append(ret)
            line = ""
            print(ret)
        # open(filename, 'w')

    def __convert_private_variable(self):
        self.__convert_variable(self.__private_variable, '-')

    def __convert_protected_variable(self):
        self.__convert_variable(self.__protected_variable, '+')

    def __convert_public_variable(self):
        self.__convert_variable(self.__public_variable, '+')

    def __convert_variable(self, filename, tag):
        text = self.__uncomment(filename)
        lines = text.split('\n')
        line = ""
        for l in lines:
            line += l.strip()
            if not line:
                continue
            if line[-1] == ';':
                line = line[:-1]
            else:
                line = line[:-1]
                continue

            n = 0
            while line[n] not in " *":
                n = n + 1
            while line[n] == '*':
                n = n - 1
            # n = line.rfind(' *')
            t = line[:n+1]
            variables = line[n+1:].split(',')
            for v in variables:
                c = v.count("*")
                ret = "%s %s : %s" % (tag, v.replace("*", "").strip(), t + '*' * c)
                print(ret)
            line = ""
        open(filename, 'w')


if __name__ == '__main__':
    convert = Convert()
    convert.convert()
