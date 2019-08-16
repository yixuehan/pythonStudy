#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import wxpy
import os

bot = wxpy.Bot(console_qr=True, cache_path=True)

bot.file_helper.send('Hello from wxpy!')

my_friends = bot.friends()

for my_friend in my_friends:
    print(my_friend)

my_groups = bot.groups(update=True)

for my_group in my_groups:
    print(my_group)

os.sys.exit(1)

names = ['何继中 智能焊接机器人', 'LHC', '三栖', '燕儿翩翩飞']

members = []

for name in names:
    found = bot.friends().search(name)
    friend = wxpy.ensure_one(found)
    print(friend)
    members.append(friend)

print(members)

group = bot.create_group(members, 'test blacklist')

print(group)

group.send_msg("test blacklist lalala")
