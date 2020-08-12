#include <iostream>
using namespace std;

#include <gst/gst.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    GstElementFactory *factory = gst_element_factory_find("fakesrc");
    if (!factory) {
        g_print("Failed to find factory of type 'fakesrc'\n");
        return -1;
    }

    GstElement *element = gst_element_factory_create(factory, "source");
    if (!element) {
        g_print("Failed to create element 'source', even though its factory 'fakesrc' exists \n");
        return -1;
    }
    gst_object_unref(GST_OBJECT(element));
    gst_object_unref(GST_OBJECT(factory));
}
