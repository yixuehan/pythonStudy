#!/usr/bin/env python3
# -*- coding: utf-8 -*-

motocycles = ['honda', 'yamaha', 'suzuki']
print(motocycles)

#del motocycles[1]
#print(motocycles)

poped = motocycles.pop()
print(motocycles)
print(poped)

players = ['charles', 'martina', 'michael', 'florence', 'eli']
player2 = players[0:3]

print(players, player2)

player2[0] = 'Charles'
print(players, player2)

