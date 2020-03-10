#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tkinter import *
btn = Button()
btn.pack()
btn['text'] = 'Click me!'
def clicked():
    print('I was clicked')

btn['command'] = clicked

mainloop()
