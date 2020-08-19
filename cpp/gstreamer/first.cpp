#include <gst/gst.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Build the pipeline */
  pipeline =
      gst_parse_launch
// ("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",
    ("playbin uri=rtsp://admin:admin@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0", 
      NULL);

  GstElement *sink;
  g_object_get(pipeline, "video-sink", &sink, nullptr);
  printf("get sink %p\n", sink);

  sink = gst_element_factory_make("ximagesink", "sink");
  printf("make sink %p\n", sink);
  g_object_set(pipeline, "video-sink", sink, nullptr);
  g_object_get(pipeline, "video-sink", &sink, nullptr);
  printf("get sink %p\n", sink);

  sink = gst_element_factory_make("ximagesink", "sink");
  printf("make sink %p\n", sink);
  g_object_set(pipeline, "video-sink", sink, nullptr);
  g_object_get(pipeline, "video-sink", &sink, nullptr);
  printf("%p\n", sink);
  /* Start playing */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg =
      gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
      (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

  /* Free resources */
  if (msg != NULL)
    gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}
