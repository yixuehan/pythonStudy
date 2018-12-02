#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def make_pizza(*toppings):
    for topping in toppings:
        print(topping)


make_pizza("abc", "hello", "egg", 10)


