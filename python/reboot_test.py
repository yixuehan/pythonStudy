#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import json
import os

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("usage:%s process_name" % sys.argv[0])
        sys.exit(1)
    os.chdir(os.path.dirname(sys.argv[0]))

    with open("config.json", "r") as f:
        config = json.load(f)
        if config["current"] >= config["end"]:
            print("done")
            sys.exit(0)
    config["current"] = config["current"] + 1
    s = json.dumps(config, separators=(",", ":"), indent=4, ensure_ascii=False)
    with open("config.json", "w") as f:
        f.write(s)

    "start test..."
    cmd = ""
    for arg in sys.argv[1:]:
        cmd += arg + ' '
    if 0 == os.system(cmd):
        os.system("reboot")
    else:
        print("test fail")
