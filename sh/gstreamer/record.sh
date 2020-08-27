#!/bin/bash

# gst-launch-1.0 -e v4l2src ! videoconvert ! x264enc ! mp4mux name=mux ! filesink location=file.mp4 alsasrc ! queue ! audioconvert ! lamemp3enc ! mux.
# gst-launch-1.0 mp4mux name=mux ! filesink location=file.mp4 v4l2src num-buffers=500 ! queue ! videoconvert ! x264enc ! mux. 
# gst-launch-1.0 qtmux name=mux ! filesink location=file.mov alsasrc ! audioconvert ! mux.audio_0 v4l2src ! videoconvert ! mux.video_0
# gst-launch-1.0 -e qtmux name=mux ! filesink location=file.mp4 v4l2src ! queue ! "video/x-raw, format=(string)YUY2, width=(int)640, height=(int)480, pixel-aspect-ratio=(fraction)1/1, framerate=(fraction)30/1" ! videoconvert ! x264enc tune=zerolatency ! mux. alsasrc ! queue ! voaacenc ! mux.

# gst-launch-1.0 -e qtmux name=mux ! filesink location=file.mp4 v4l2src ! queue ! "video/x-raw, format=(string)YUY2, width=(int)640, height=(int)480, pixel-aspect-ratio=(fraction)1/1, framerate=(fraction)30/1" ! videoconvert ! x264enc tune=zerolatency ! mux.

# gst-launch-1.0 -e avimux name=mux ! filesink location=file.avi v4l2src ! videoconvert ! x264enc ! mux.video_0 pulsesrc device=alsa_input.pci-0000_00_0e.0.analog-stereo ! voaacenc ! queue ! mux.audio_0
# gst-launch-1.0 -v v4l2src ! videoconvert ! x264enc ! mux. alsasrc ! vorbisenc ! oggmux ! mux. avimux name=mux ! filesink location=test.avi
# gst-launch-1.0 v4l2src ! videoconvert ! autovideosink  alsasrc ! audioconvert ! autoaudiosink

# error
# gst-launch-1.0 -e v4l2src ! videoscale ! videoconvert ! tee name=t ! queue ! autovideosink t. ! queue ! x264enc ! mp4mux name=mux ! filesink location=file.mp4 alsasrc ! audioconvert ! lamemp3enc ! mux.

# gst-launch-1.0 -e filesrc location=trailer.mp4 ! qtdemux name=demux demux.video_0 ! decodebin ! videoconvert ! x264enc ! mp4mux name=mux ! filesink location=file.mp4 filesrc location=test.mp3 ! queue ! decodebin ! audioconvert ! lamemp3enc ! mux.

# gst-launch-1.0 -e filesrc location=trailer.mp4 ! qtdemux name=demux demux.video_0 ! decodebin ! videoconvert ! x264enc ! mp4mux name=mux ! filesink location=file.mp4 filesrc location=test.mp3 ! decodebin ! audioconvert ! lamemp3enc ! mux.

# gst-launch-1.0 -e mp4mux name=mux ! filesink location= file.mp4 filesrc location=trailer.mp4 ! qtdemux name=demux demux.video_0 ! decodebin ! videoconvert ! x264enc ! mux. filesrc location=test.mp3 ! queue ! decodebin ! audioconvert ! lamemp3enc ! mux.

# gst-launch-1.0 -e filesrc location=trailer.mp4 ! qtdemux name=demux demux.video_0 ! decodebin ! videoconvert ! autovideosink filesrc location=test.mp3 ! queue ! decodebin ! audioconvert ! autoaudiosink
gst-launch-1.0 filesrc location=test.mp4 ! avidemux name=demux demux.video_0 ! decodebin ! videoconvert ! xvimagesink 

# gst-launch-1.0 -e v4l2src ! videorate ! tee name=myvid \
#       ! queue ! decodebin ! xvimagesink sync=false \
#       myvid. ! queue ! mux.video_0 \
#       alsasrc ! audioconvert ! lamemp3enc ! queue ! mux.audio_0 \
#       avimux name=mux ! filesink location=/tmp/out.avi

# gst-launch-1.0 -e alsasrc ! audioconvert ! lamemp3enc ! qtmux ! filesink location=audio.mov v4l2src ! videoconvert ! avimux ! filesink location=video.avi

# gst-launch-1.0 -e mp4mux name=mux ! filesink location=file.mp4 sync=true alsasrc ! queue ! audioconvert ! audioresample ! lamemp3enc ! mux.audio_0 v4l2src ! queue ! videorate ! videoconvert ! x264enc tune=zerolatency ! mux.video_0

# gst-launch-1.0 -e v4l2src device=/dev/video0 ! \
#      "video/x-raw, format=(string)YUY2, width=(int)640, height=(int)480" ! \
#     videoconvert ! \
#     x264enc ! \
#     avimux ! \
#     filesink location="test.mp4"
    # xvimagesink sync=false
