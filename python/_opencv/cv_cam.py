#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cv2
import time

video = cv2.VideoCapture()

# video.open(0)
# video.open("v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 \
#        ! videoconvert ! video/x-raw,format=(string)BGRx ! appsink",
#            cv2.CAP_GSTREAMER)
# video.open("v4l2src device=/dev/video0 !"
#            "video/x-raw, width=(int)640, height=(int)480, format=(string)BGRx ! "
#            "videoconvert ! appsink",
#            cv2.CAP_GSTREAMER)
# video.open("rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1")
# video.open("rtsp://admin:admin123456@103.46.128.45:23507/cam/realmonitor?channel=1&subtype=1")
# video.open("rtsp://admin:admin123456@w505703394.e2.luyouxia.net:26365/cam/realmonitor?channel=1&subtype=1")
# video.open("rtsp://admin:admin123456@w505703394.e2.luyouxia.net:24824/cam/realmonitor?channel=1&subtype=1")
# video.open("rtsp://192.168.1.108:554/cam/realmonitor?channel=1&subtype=1")
video.open("rtsp://admin:admin123456@118.24.20.35:554/cam/realmonitor?channel=1&subtype=1")
# video.open(1)

# video.set()

fps = 0
last_time = time.time()
# video.open("rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0")
# video.open(1)

# video.set()
video_fps = video.get(cv2.CAP_PROP_FPS)
print("current fps:", video_fps)
# video.set(cv2.CAP_PROP_FPS, 5)
# print("current fps:", video.get(cv2.CAP_PROP_FPS))
size = (int(video.get(cv2.CAP_PROP_FRAME_WIDTH)),
        int(video.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print("current size:", size)

last_time = time.time()
fps = 0
# fourcc = cv2.VideoWriter_fourcc(*'XVID')
# writer = cv2.VideoWriter("b.avi", fourcc, video_fps, size)
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
    else:
        break
    current_time = time.time()
    # writer.write(img)
    if current_time - last_time >= 1:
        print("fps:", fps)
        fps = 0
        last_time = current_time
