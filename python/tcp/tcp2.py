#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    address = ("127.0.0.1", 12345)
    sock.bind(address)
    sock.listen(10)
    conn_sock, conn_addr = sock.accept()
    msg = conn_sock.recv(1024)
    print("msg:", msg)
    print("sockname:%s addr:%s" % (conn_sock.getsockname(), conn_addr))
