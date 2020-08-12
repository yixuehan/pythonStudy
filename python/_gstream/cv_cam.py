#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cv2
import time

video = cv2.VideoCapture()

# video.open(2)
# video.open("v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 \
# ! videoconvert ! video/x-raw,format=(string)BGRx ! appsink",
#            cv2.CAP_GSTREAMER)
# video.open("v4l2src device=/dev/video0 !"
#            "video/x-raw, width=(int)640, height=(int)480, format=(string)BGRx ! "
#            "videoconvert ! appsink",
#            cv2.CAP_GSTREAMER)
video.open("rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1")
# video.open(1)

# video.set()

fps = 0
last_time = time.time()
# video.open("rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0")
# video.open(1)

# video.set()
print("current fps:", video.get(cv2.CAP_PROP_FPS))
# video.set(cv2.CAP_PROP_FPS, 5)
# print("current fps:", video.get(cv2.CAP_PROP_FPS))

last_time = time.time()
fps = 0
while True:
    # while video.grab():
    #     ok, img = video.retrieve()
    #     if not ok:
    #         break
    #     cv2.imshow("capture", img)
    #     if cv2.waitKey(1000) & 0xFF == ord('q'):
    #         break
    #     print("grab total frames:", video.get(cv2.CAP_PROP_FRAME_COUNT))
    #     print("清除")
    ok, img = video.read()
    if ok:
        # 清缓存
        cv2.imshow("capture", img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        t = time.time()
        fps = fps + 1
    current_time = time.time()
    if current_time - last_time > 1:
        print("fps:", fps)
        fps = 0
        last_time = current_time
