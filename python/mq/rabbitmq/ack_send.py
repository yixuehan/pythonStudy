#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
from pika import spec

credentials = pika.PlainCredentials("user1", "user1")


connection = pika.BlockingConnection(
        # parameters=pika.ConnectionParameters(host="192.168.39.221", port=5672,
        parameters=pika.ConnectionParameters(host="192.168.137.41", port=5672,
                                             virtual_host='user1',
                                             credentials=credentials))

channel = connection.channel()


res = channel.exchange_declare("exchange_ack", durable=True)
print(res)
res = channel.queue_declare(queue='queue_ack', durable=True)
print(res)
res = channel.queue_bind(queue='queue_ack', exchange='exchange_ack')
print(res)

channel.confirm_delivery()

# print(res)
message = ""
for i in range(10240):
    message += 'hello world test ack %s' % i

channel.basic_publish(
    exchange='exchange_ack',
    routing_key='queue_ack',
    body=message,
    properties=pika.spec.BasicProperties(
        content_type='text/plain',
        delivery_mode=2,
        expiration=5))  # , mandatory=True)

# print(res)
# properties=pika.spec.BasicProperties(delivery_mode=2))
# print("send message:", message)


# channel = connection.channel(on_open_callback=open_callback)


def confirm_callback(frame):
    print(frame)
    print(frame.method)
    if type(frame.method) == spec.Basic.Nack:
        print("Message lost!")
