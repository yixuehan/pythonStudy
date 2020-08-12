#!/bin/bash
# gst-launch-1.0 audiotestsrc freq=215.0 ! tee name=t ! queue ! audioconvert ! audioresample ! autoaudiosink \
#                                                  t. ! queue ! wavescope shader=0 style=0 ! videoconvert ! autovideosink
