#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import subprocess
# import sys


# class FlushFile(object):
#     """Write-only flushing wrapper for file-type objects."""
#     def __init__(self, f):
#         self.f = f

#     def write(self, x):
#         self.f.write(str(x))
#         self.f.flush()


# sys.stdout = FlushFile(sys.__stdout__)

def __external_cmd(cmd, code="utf8"):
    print(cmd)
    process = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    while process.poll() is None:
        line = process.stdout.readline()
        # line = line.strip()
        if line:
            print(line.decode(code, 'ignore'), end="")


# popen = subprocess.Popen(['ping', 'www.baidu.com', '-n', '3'], stdout=subprocess.PIPE)


# while True:
#     next_line = popen.stdout.readline()
#     if next_line == '' and popen.poll() is not None:
#         break
#     sys.stdout.write(str(next_line))


# __external_cmd(['ping', 'www.baidu.com', '-c', '3'])
__external_cmd('ping www.baidu.com -c 3')
