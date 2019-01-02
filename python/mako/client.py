#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import mako, template

#print(template.Template(filename = "./client.mako").render(service_names = '("api", "create_job")'))
print(template.Template(filename = "./client.mako").render()
print(template.Template(filename = "./test.mako").render())
