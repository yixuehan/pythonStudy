#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time

symbols = '$¢£¥€¤'

beg = time.clock()

for i in range(0, 1000000):
    beyond_ascii = [ord(s) for s in symbols if ord(s) > 127]

end = time.clock()

print(end-beg)

begin = time.clock()

for i in range(0, 1000000):
    beyond_ascii = list(filter(lambda c:c > 127, map(ord, symbols)))

end = time.clock()

print(end-beg)

print(beyond_ascii)

