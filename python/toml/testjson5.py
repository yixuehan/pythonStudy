#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json5

with open("api.json5") as filejson:
    jsondict = json5.load(filejson)
    print(jsondict)
