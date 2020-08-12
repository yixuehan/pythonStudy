#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from flask import Flask
app = Flask(__name__)
@app.route('/')
def powers(n=10):
    return ', '.join(str(2**i) for i in range(n))
