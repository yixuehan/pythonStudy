#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itchat
import time
import os

itchat.auto_login(hotReload = True, enableCmdQR=2)

members = itchat.get_friends(update = True)

f = open("frends.txt", "w")

for m in members:
    f.write(str(m) + "\n")

f.close()

i = 0

ms = []

#ms.append(itchat.search_friends(nickName = 'LHC'))

ms.append(itchat.search_friends(wechatAccount = 'clhc2011'))
ms.append(itchat.search_friends(wechatAccount = 'jizhonghe2000'))

print(ms)

#os.exit(1)

#while i < len(members):
#    itchat.create_chatroom(members[i:i+40], 'test chatroom')
#    i = i + 40








