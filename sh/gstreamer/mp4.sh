#!/bin/bash
gst-launch-1.0 filesrc location=${HOME}/tmp/trailer.mp4 ! qtdemux name=demux demux.audio_0 ! queue ! decodebin ! audioconvert ! autoaudiosink demux.video_0 ! queue ! decodebin ! videoconvert ! autovideosink
