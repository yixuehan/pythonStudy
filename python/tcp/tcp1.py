#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_addr = ("127.0.0.1", 12346)

    sock.bind(sock.getsockname())
    sock.listen(10)
    address = ("127.0.0.1", 12345)
    sock.connect(address)
    print("sockname:", sock.getsockname())
    sock.send("hello".encode())
    connfd = sock.accept()
    msg = connfd.recv()
    print("msg:", msg)
