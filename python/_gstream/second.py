#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gi
# from gi.repository import Gst, GObject, GLib
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib

Gst.init(None)
a = 0


def on_pad_added(src, pad, des):
    vpad = des.get_static_pad("sink")
    pad.link(vpad)


pipe = Gst.Pipeline.new("test")

src = Gst.ElementFactory.make("rtspsrc", "src")
assert src
src1 = Gst.ElementFactory.make("rtspsrc", "src1")
assert src1
depayv = Gst.ElementFactory.make("rtph264depay", "depayv")
assert depayv
depaya = Gst.ElementFactory.make("rtppcmadepay", "depaya")
assert depaya
# tee = Gst.ElementFactory.make("tee", "tee")
queuev = Gst.ElementFactory.make("queue", "queuev")
assert queuev
queuea = Gst.ElementFactory.make("queue", "queuea")
assert queuea
src.connect("pad-added", on_pad_added, queuev)
src1.connect("pad-added", on_pad_added, queuea)

vfilter = Gst.ElementFactory.make("capsfilter", "flt")
assert vfilter
caps = Gst.Caps.from_string("video/x-h264, width=(int)640, height=(int)480")
assert caps
vfilter.set_property("caps", caps)

afilter = Gst.ElementFactory.make("capsfilter", "aflt")
assert afilter
audio_caps = Gst.Caps.from_string("audio/x-alaw, channels=(int)1, rate=(int)8000")
assert audio_caps
afilter.set_property("caps", audio_caps)

muxer = Gst.ElementFactory.make("matroskamux", "muxer")
assert muxer
sink = Gst.ElementFactory.make("filesink", "sinka")
assert sink

# rstp = 'rtsp://adminpassword@IP/Streaming/channels/802'
rstp = 'rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1'
src.set_property("location", rstp)
src1.set_property("location", rstp)
pipe.add(src)
pipe.add(src1)
pipe.add(depayv)
pipe.add(depaya)
pipe.add(queuev)
pipe.add(vfilter)
pipe.add(afilter)
pipe.add(queuea)
pipe.add(sink)
pipe.add(muxer)

queuev.link(depayv)
depayv.link(vfilter)
queuea.link(depaya)
depaya.link(afilter)

vmuxpad = muxer.get_request_pad("video_%u")
assert vmuxpad
vsrcpad = vfilter.get_static_pad("src")
assert vsrcpad
vsrcpad.link(vmuxpad)

amuxpad = muxer.get_request_pad("audio_%u")
assert amuxpad
asrcpad = afilter.get_static_pad("src")
assert asrcpad
asrcpad.link(amuxpad)
muxer.link(sink)
print(sink.get_property("location"))
sink.set_property("location", 'artspAV2.mkv')

print(sink.get_property("location"))
pipe.set_state(Gst.State.PLAYING)

mainloop = GLib.MainLoop()
assert mainloop
mainloop.run()
