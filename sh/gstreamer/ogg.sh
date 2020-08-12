#!/bin/bash
gst-launch-1.0 filesrc location=alsasrc.ogg ! decodebin ! tee name=t ! queue ! audioconvert ! audioresample ! autoaudiosink t. ! queue ! audioconvert ! goom ! videoconvert ! autovideosink

