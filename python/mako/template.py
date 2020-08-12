#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from mako.template import Template

t = Template('hello, ${name}!')

print(t.render(name='yeolar'))


