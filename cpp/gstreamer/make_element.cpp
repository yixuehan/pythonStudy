#include <iostream>
using namespace std;

#include <gst/gst.h>
// using namespace boost;

int main(int argc, char *argv[])
{
    GstElement *element;

    gst_init(&argc, &argv);

    element = gst_element_factory_make("fakesrc", "source");

    if (!element) {
        g_print("Failed to create element of type 'fakesrc'\n");
        return -1;
    }
    gst_object_unref(GST_OBJECT(element));
    return 0;
}
