#include <gst/gst.h>
#include <cstdio>
#include <cassert>

void check_element(GstElement *e)
{
    assert(e != nullptr &&  "element is null");
}

GstElement *get_element(const char *component, const char *element_name)
{
    auto e = gst_element_factory_make(component, element_name);
    check_element(e);
    return e;
}

gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
    GMainLoop *loop = (GMainLoop*)data;
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_EOS:
        printf("End of stream\n");
        g_main_loop_quit(loop);
        break;
    case GST_MESSAGE_ERROR:
    {
        gchar *debug;
        GError *error;
        gst_message_parse_error(msg, &error, &debug);
        g_free(debug);
        printf("Error:%s\n", error->message);
        g_error_free(error);
        g_main_loop_quit(loop);
        break;
    }
    default:
        break;
    }
    return true;
}


int main(int argc, char *argv[])
{
    GMainLoop *loop;
    GstElement *pipeline, *source, *video_raw, *video_convert, *sink;
    GstBus *bus;
    guint bus_watch_id;
    gst_init(&argc, &argv);
    loop = g_main_loop_new(nullptr, false);
    if (argc != 2) {
        printf("Usage:%s <video device>\n", argv[0]);
        return -1;
    }
    pipeline = gst_pipeline_new("my_video-player");
    source = get_element("v4l2src", "src_device");
    // g_object_set(G_OBJECT(source), "device", argv[1], nullptr);
    // video_raw = get_element("video/x-raw", "video_raw");
    // g_object_set(G_OBJECT(video_raw), "width", 640, "height", 480,
    //              "format", "(string)YUY2");
    video_convert = get_element("videoconvert", "convert");
    sink = get_element("xvimagesink", "mysink");
    // g_object_set(G_OBJECT(sink), "-e");
    //
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    // gst_bus_add_watch(bus, bus_call, loop);
    bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);
    gst_object_unref(bus);

    gst_bin_add_many(GST_BIN(pipeline),
            source, video_convert, sink, nullptr);
    gst_element_link(source, video_convert);
    gst_element_link_many(video_convert, sink, nullptr);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    g_main_loop_run(loop);

    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    g_source_remove(bus_watch_id);
    g_main_loop_unref(loop);
    return 0;
}
