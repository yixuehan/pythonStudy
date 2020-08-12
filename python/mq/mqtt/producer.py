#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt


def on_connect(client, userdata, flags, rc):
    print("rc:" + str(rc))


def on_message(client, userdata, msg):
    print(msg.topic, str(msg.payload))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
# client.on_disconnect
client.connect('0.0.0.0', 1883)
client.publish('test001', payload='hello mqtt', qos=1)
