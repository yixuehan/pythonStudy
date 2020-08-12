#!/bin/bash
# gst-launch-1.0 v4l2src device=/dev/video1 ! 'video/x-raw, \
#   width=(int)1920, height=(int)1080, format=(string)YUY2, \
#   framerate=(fraction)30/1' ! autovideosink

# gst-launch-1.0 videotestsrc ! 'video/x-raw, format=(string)GRAY8, \
#   width=(int)640, height=(int)480, framerate=(fraction)30/1' ! \
#   nvvidconv ! 'video/x-raw(memory:NVMM), format=(string)I420' ! \
#   nvv4l2h264enc ! 'video/x-h264, \
#   stream-format=(string)byte-stream' ! h264parse ! qtmux ! \
#   filesink location=test.mp4 -e

# gst-launch-1.0 v4l2src ! 'video/x-raw, \
#   width=(int)640, height=(int)480, framerate=(fraction)30/1' ! \
#   autovideoconvert ! jpegdec ! autovideosink

# gst-launch-1.0 v4l2src ! 'video/x-raw, \
#   width=(int)640, height=(int)480, framerate=(fraction)30/1' ! \
#   videoconvert ! qtmux ! \
#   filesink location=test.mp4 -e

# gst-launch-1.0 v4l2src device="/dev/video1" ! \
#   "video/x-raw, width=640, height=480, format=(string)YUY2" ! \
#   filesink location=./a.mp4 -e

gst-launch-1.0 v4l2src device="/dev/video0" ! \
  "video/x-raw, width=640, height=480, format=(string)YUY2" ! \
  videoconvert ! \
  xvimagesink -e
