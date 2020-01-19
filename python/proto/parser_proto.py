#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import protobuf_to_dict as pb_parser

message = pb_parser.Message()

with open("./taskmanager.proto", "rb") as fp:
    pb_buf = fp.read()

message.MergeFromString(pb_buf)

pb_parser.dict_to_protobuf(message)
