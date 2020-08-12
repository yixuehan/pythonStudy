#!/bin/bash
gst-launch-1.0 -e videomixer name=mix \
    sink_0::xpos=0 sink_0::ypos=0 \
    sink_1::xpos=300 sink_1::ypos=300 \
    ! autovideosink sync=false \
    v4l2src ! videoconvert ! mix.sink_0 \
    rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! mix.sink_1
