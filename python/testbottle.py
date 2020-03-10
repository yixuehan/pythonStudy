#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import bottle
# from bottle import route, run

bot = bottle.Bottle()

# add_route(hello)


@bot.route('/hello')
def hello():
    return 'Hello world'


bot.run(host='0.0.0.0', port=8080)
# bottle.run(bot, host='0.0.0.0', port=8080)
