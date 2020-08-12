#!/usr/bin/env python3
import itertools

l3 = [{1: "abc", 2: "xyz"}, {3, 4}, {5, 6}]
for a, b in l3:
    print(a, b)

l1 = [1, 2, 3, 4, 5]
l2 = ["abc", "xya"]
print("*" * 80)
for x, y in zip(l1, l2):
    print(x, y)

print("*" * 80)
coms = list(itertools.combinations([1, 2, 3, 4], 1))
for com in coms:
    for e in com:
        print(e)
