#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
import time

credentials = pika.PlainCredentials("user1", "user1")

connection = pika.BlockingConnection(
        # parameters=pika.ConnectionParameters(host="192.168.39.221", port=5672,
        parameters=pika.ConnectionParameters(host="192.168.137.41", port=5672,
                                             virtual_host='user1',
                                             credentials=credentials))

channel = connection.channel()

res = channel.exchange_declare("exchange2", durable=True)
print(res)

res = channel.queue_declare(queue='queue2', durable=True)
print(res)

res = channel.queue_bind(queue='queue1', exchange='exchange2')
print(res)
res = channel.queue_bind(queue='queue2', exchange='exchange2')
print(res)

for i in range(1024 * 1024 * 1024):
    message = 'hello world %s' % i
    channel.basic_publish(exchange='exchange2', routing_key='queue1', body=message, properties=pika.spec.BasicProperties(delivery_mode=2))
    # time.sleep(1)
