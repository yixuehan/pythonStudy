#!/bin/bash
# GST_DEBUG=4 GST_DEBUG_NO_COLOR=1 AWS_ACCESS_KEY_ID=$1 AWS_SECRET_ACCESS_KEY=$2 AWS_DEFAULT_REGION="us-east-1" gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! x264enc ! mp4mux ! filesink location="rtsp.mp4"
# 播放
# GST_DEBUG=4 GST_DEBUG_NO_COLOR=1 AWS_ACCESS_KEY_ID=$1 AWS_SECRET_ACCESS_KEY=$2 AWS_DEFAULT_REGION="us-east-1" gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! autovideosink sync=false

# GST_DEBUG=4 GST_DEBUG_NO_COLOR=1 AWS_ACCESS_KEY_ID=$1 AWS_SECRET_ACCESS_KEY=$2 AWS_DEFAULT_REGION="us-east-1" gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! autovideosink name=sink_name sync=false v4l2src ! videoconvert ! autovideosink sync=false

# GST_DEBUG=4 GST_DEBUG_NO_COLOR=1 AWS_ACCESS_KEY_ID=$1 AWS_SECRET_ACCESS_KEY=$2 AWS_DEFAULT_REGION="us-east-1" gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! autovideosink name=sink_name sync=false v4l2src ! videoconvert ! autovideosink sync=false

# gst-launch-1.0 -e v4l2src ! videoconvert ! autovideosink sync=false

# gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! autovideosink sync=false
# GST_DEBUG=4 GST_DEBUG_NO_COLOR=1 AWS_ACCESS_KEY_ID=$1 AWS_SECRET_ACCESS_KEY=$2 AWS_DEFAULT_REGION="us-east-1" gst-launch-1.0 rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! rtph264depay ! video/x-h264,format=avc,stream-format=avc,alignment=au ! h264parse ! filesink location="rtsp.mp4"

# 录制
# gst-launch-1.0 -e mp4mux name=mux ! filesink location="rtsp.mp4" rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! queue ! decodebin ! x264enc tune=zerolatency ! mux. alsasrc ! queue ! voaacenc ! mux.

# gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! videoconvert ! "video/x-raw,width=1280,heiht=720" ! autovideosink sync=false
# gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! videoconvert ! videoscale !  "video/x-raw,width=1280,height=720" ! autovideosink sync=false
# gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0" short-header=true ! decodebin ! videoconvert ! "video/x-raw" ! ximagesink
gst-launch-1.0 -e rtspsrc location="rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1" short-header=true ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! xvimagesink sync=false
