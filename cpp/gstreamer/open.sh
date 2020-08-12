#!/bin/bash
# gst-launch-1.0 v4l2src device=/dev/video0 num-buffers=10000 ! video/x-raw,format=YUY2,width=160,height=120,framerate=30/1  ! videoconvert ! autovideosink
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! video/x-raw,format=BGR ! appsink
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! video/x-raw ! autovideosink
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! v4l2sink device=/dev/video1
# gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! filesink location=./video.mp4
# gst-launch-1.0 rtspsrc latency=2000 location="rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" ! rtph264depay ! queue ! h264parse ! autovideosink
# gst-launch-1.0 rtspsrc "location=rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! fakesink
# gst-launch-1.0 rtspsrc debug=1 location="rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=3&subtype=0" ! rtph264depay ! h264parse ! omxh264dec ! videoconvert ! autovideosink
# gst-launch-1.0 rtspsrc "location=rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! rtph264depay ! h264parse ! openh264dec ! d3dvideosink
# gst-launch-1.0 rtspsrc "location=rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! rtph264depay ! h264parse ! mp4mux ! filesink location=./rtsp.h264
# gst-launch-1.0 rtspsrc latency=2000 location="rtsp://admin:admin123456@192.168.1.108/cam/realmonitor?channel=1&subtype=1" ! rtph264depay ! queue ! h264parse ! nvv4l2decoder ! fakesink
gst-launch-1.0 rtspsrc "location=rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! rtph264depay ! queue ! h264parse ! avdec_h264 ! fakesink
# gst-launch-1.0 rtspsrc latency=2000 location="rtsp://admin:admin@192.168.1.108" ! rtph264depay ! queue ! h264parse ! nvv4l2decoder ! fakesink
# gst-launch-1.0 rtspsrc "location=rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink
# gst-launch-1.0 rtspsrc debug=1 location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! decodebin ! queue ! fakesink
# gst-launch-1.0 rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" ! avmux_rtsp! autovideosink
