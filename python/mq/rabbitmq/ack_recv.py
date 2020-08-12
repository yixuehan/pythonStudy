#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
# import time

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

# channel.get_waiting_message_count


def callback(channel, method, properties, body):
    print(body.decode())
    channel.basic_ack(delivery_tag=method.delivery_tag)
    # print(channel, method, properties)
    # print("waiting message:", channel.get_waiting_message_count())
    # if channel.get_waiting_message_count() == 0:
    #     channel.close()


res = channel.basic_consume(queue='queue_ack', on_message_callback=callback, exclusive=False)
print(res)

# print("waiting message:", channel.get_waiting_message_count())

channel.start_consuming()
