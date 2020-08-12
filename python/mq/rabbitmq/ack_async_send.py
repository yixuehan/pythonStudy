#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
from pika import spec

credentials = pika.PlainCredentials("user1", "user1")


def connection_on_open(connection):
    connection.channel(on_open_callback=channel_on_open)


count = 10240

# connection = pika.BlockingConnection(
connection = pika.SelectConnection(
        # parameters=pika.ConnectionParameters(host="192.168.39.221", port=5672,
        parameters=pika.ConnectionParameters(host="192.168.137.41", port=5672,
                                             virtual_host='user1',
                                             credentials=credentials),
        on_open_callback=connection_on_open)


g_channel = None


def channel_on_open(channel):
    global g_channel
    g_channel = channel
    res = channel.exchange_declare("exchange_ack", durable=True)
    print(res)
    res = channel.queue_declare(queue='queue_ack', durable=True)
    print(res)
    res = channel.queue_bind(queue='queue_ack', exchange='exchange_ack')
    print(res)
    channel.confirm_delivery(ack_nack_callback=confirm_callback)
    # print(res)
    # for i in range(10240):
    global count
    if count > 0:
        message = 'hello world test ack %s' % count
        channel.basic_publish(
            exchange='exchange_ack',
            routing_key='queue_ack',
            body=message,
            properties=pika.spec.BasicProperties(content_type='text/plain', delivery_mode=2))
        count = count - 1
        # properties=pika.spec.BasicProperties(delivery_mode=2))
        # print("send message:", message)


# channel = connection.channel(on_open_callback=open_callback)


def confirm_callback(frame):
    print(frame)
    print(frame.method)
    global count
    if type(frame.method) == spec.Basic.Nack:
        print("Message lost! 重发")
        count = count + 1

    if count > 0:
        message = 'hello world test ack %s' % count
        g_channel.basic_publish(
            exchange='exchange_ack',
            routing_key='queue_ack',
            body=message,
            properties=pika.spec.BasicProperties(content_type='text/plain', delivery_mode=2))
        count = count - 1


connection.ioloop.start()
