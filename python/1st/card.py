#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import collections
import random

Card = collections.namedtuple('Card', ['rank', 'suit'])

class FrenchDeck:
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs harts'.split()

    def __init__(self):
        self._cards = [Card(rank, suit) for suit in self.suits
                                        for rank in self.ranks]
        #print(self._cards)

    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]


deck = FrenchDeck()
#print(len(deck))
print(random.choice(deck))
print(deck[:3])
print(deck[12::13])
#for card in deck: #doctest: +ELLIPSIS
#    print(card)
#
#for card in reversed(deck):#doctest: +ELLIPSIS
#    print(card)

x = 'abc'
l = [ord(x) for x in x]
print(x)
print(l)
