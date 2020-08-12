#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono;

#include <gst/gst.h>

using GstElementPtr = GstElement *;
GstElementPtr mp4mux_, video_source_, video_convert_, audio_source_, audio_convert_, pipeline_, 
            media_sink_;

gboolean busCall(GstBus *bus, GstMessage *msg, gpointer data)
{
    printf("bus:%p msg:%p data:%p\n", bus, msg, data);
    GMainLoop *loop = (GMainLoop*)data;
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            g_print("End of stream\n");
            g_main_loop_quit(loop);
            break;
        case GST_MESSAGE_ERROR:
        {
            gchar *debug;
            GError *error;
            gst_message_parse_error(msg, &error, &debug);
            g_free(debug);
            g_printerr("Error:%s\n", error->message);
            g_error_free(error);
            g_main_loop_quit(loop);
            break;
        }
        default:
            break;
    }
    return true;

}

void sigintHandler(int ) {
    g_print("You ctrl-c-ed! Sending EoS");
    gst_element_send_event(pipeline_, gst_event_new_eos()); 
}


int testRecord()
{
    gst_init(nullptr, nullptr);
    string audio_sink_filename_ = "test.mp4";
    GMainLoop *loop = g_main_loop_new(nullptr, false);
#if 1
    pipeline_ = gst_pipeline_new("pipeline_name");

    mp4mux_ = gst_element_factory_make("mp4mux", "mux");
    media_sink_ = gst_element_factory_make("filesink", "file");
    g_object_set(media_sink_, "location", audio_sink_filename_.c_str(), nullptr);

    video_source_ = gst_element_factory_make("v4l2src", "video_src");
    // g_object_set(video_source_, "device", "/dev/video0", nullptr);
    auto video_queue = gst_element_factory_make("queue", "video_queue");
    video_convert_ = gst_element_factory_make("videoconvert", "video_convert");
    auto video_enc = gst_element_factory_make("x264enc", "enc");
    g_object_set(video_enc, "tune", 4, nullptr);
    // g_object_set(video_enc, "tune", "zerolatency", nullptr);

    audio_source_ = gst_element_factory_make("alsasrc", "audio_src");
    auto audio_queue = gst_element_factory_make("queue", "audio_queue");
    auto audio_enc = gst_element_factory_make("voaacenc", "audio_enc");

    gst_bin_add_many(GST_BIN(pipeline_), mp4mux_, media_sink_, video_source_, video_queue, video_convert_, video_enc, 
                      audio_source_, audio_queue, audio_enc, nullptr);
    if (!gst_element_link_many(video_source_, video_queue, video_convert_, video_enc, mp4mux_, nullptr)) {
        printf("link video error ...\n");
        return 1;
    }
    if (!gst_element_link_many(audio_source_, audio_queue, audio_enc,  mp4mux_, nullptr)) {
        printf("link audio error ...\n");
        return 1;
    }

    if (!gst_element_link_many(mp4mux_, media_sink_, nullptr)) {
        printf("link mux error ...\n");
        return 1;
    }
#else

    // auto cmd = R"(mp4mux name=mux ! filesink location=file.mp4 v4l2src ! queue ! "video/x-raw, format=(string)YUY2, width=(int)640, height=(int)480, pixel-aspect-ratio=(fraction)1/1, framerate=(fraction)30/1" ! videoconvert ! x264enc tune=zerolatency ! mux. alsasrc ! queue ! voaacenc ! mux.)";
    auto cmd = R"(mp4mux name=mux ! filesink location=file.mp4 v4l2src ! queue ! "video/x-raw, format=(string)YUY2, width=(int)640, height=(int)480, pixel-aspect-ratio=(fraction)1/1, framerate=(fraction)30/1" ! videoconvert ! x264enc tune=zerolatency ! mux. alsasrc ! queue ! voaacenc ! mux.)";
    pipeline_ = gst_parse_launch(cmd, nullptr);
#endif

    /* Wait until error or EOS */
    auto bus = gst_element_get_bus (pipeline_);
    auto bus_watch_id = gst_bus_add_watch(bus, busCall, loop);
    gst_element_set_state (pipeline_, GST_STATE_PLAYING);
    printf("bus:%p pipeline:%p loop:%p\n", bus, pipeline_, loop);
    std::thread t ([&]{
            std::this_thread::sleep_for(2s);
            gst_element_send_event(pipeline_, gst_event_new_eos());
            });
    g_main_loop_run(loop);
    t.join();
    gst_object_unref (bus);
    gst_element_set_state (pipeline_, GST_STATE_NULL);
    g_source_remove(bus_watch_id);
    gst_object_unref (pipeline_);
    return 0;
}

int main()
{
    // signal(SIGINT, sigintHandler);
    testRecord();
}
