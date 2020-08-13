#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import platform

if platform.system() == 'Linux':
    import distro

print(distro.linux_distribution())
