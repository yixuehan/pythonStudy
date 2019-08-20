#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def func(a, b, **kwargs):
    print(a, b)


args = {'a': 10, 'b': 20}

func(a=1, b=2, **args)
