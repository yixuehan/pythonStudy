#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itchat
import time
import os

itchat.auto_login(hotReload = True, enableCmdQR=2)

members = itchat.get_friends(update = True)

f = open("friends.txt", "w")

for m in members:
    f.write(str(m) + "\n")

f.close()

os.sys.exit(1)

i = 0

ms = []

nickNames = ['何继中 智能焊接机器人', 'LHC', '三栖', '燕儿翩翩飞']

#ms.append(itchat.search_friends(nickName = 'LHC'))

for member in members:
    if member['NickName'] in nickNames:
        friends = itchat.search_friends(userName = member['UserName'])
        for friend in friends:
            print(friend)
            ms.append(friend)

print("*" * 80)
print(ms)
chatroomUserName = itchat.create_chatroom(ms, 'test backlist')
print(chatroomUserName)
itchat.send('代码测试黑名单', chatroomUserName)
os.sys.exit(1)

f = open("rooms.txt", "w")
rooms = itchat.get_chatrooms(update = True)
for room in rooms:
    print(room['NickName'])
    f.write(str(room) + "\n")
    if room['NickName'] == '▄█▀█●':
        print("发送")
        print(itchat.send('代码测试黑名单', room['UserName']))
        os.sys.exit(1)
f.close()

#os.exit(1)

#while i < len(members):
#    itchat.create_chatroom(members[i:i+40], 'test chatroom')
#    i = i + 40








