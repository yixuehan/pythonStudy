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

# res = channel.queue_declare(queue='queue2')

# res = channel.queue_bind(exchange='', queue='queue1')

# print(res)


def callback(ch, method, properties, body):
    print(body.decode())
    time.sleep(1)
    ch.basic_ack(delivery_tag=method.delivery_tag)

channel.basic_qos(prefetch_count=10)


channel.basic_consume(queue='queue1', on_message_callback=callback, exclusive=False)

channel.start_consuming()
