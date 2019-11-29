# -*- coding: utf-8 -*-
import turtle
import time

turtle.screensize(800, 600, "green")
turtle.fillcolor("red")
turtle.speed(0)
turtle.begin_fill()
while True:
    turtle.forward(200)
    turtle.right(144)
    if abs(turtle.pos()) < 1:
        break
turtle.end_fill()
input()
