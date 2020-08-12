#include <gst/gst.h>

void my_signal(gpointer *instance, gchar *buffer, gpointer userdata)
{
    g_print ("my_signal_handler said: %s\n", buffer);
    g_print ("my_signal_handler said: %s\n", (gchar *)userdata);
}

int main()
{
    gst_init(nullptr, nullptr);
    auto loop = g_main_loop_new(nullptr, false);

    g_main_loop_run(loop);
}
