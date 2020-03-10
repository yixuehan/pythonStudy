#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import toml

t = toml.load("a.toml")
print(t)

print(toml.dumps(t))
