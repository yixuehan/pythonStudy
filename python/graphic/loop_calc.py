# -*- coding: utf-8 -*-
from functools import reduce

def factorial(n):
    print(n)
    return reduce(lambda x,y:x*y, range(1, n+1))

if __name__ == '__main__':
    print("请输入最大阶乘的分母:")
    count = input()
    count = int(count)
    if count % 2 == 0:
        print("必须输入奇数，当前输入为[%s]" % count)
        assert False
    r = 0
    for i in range(1, count+1)[0::2]:
        r += 1 / factorial(i)
    print(r)
    print("%.2f" % r)