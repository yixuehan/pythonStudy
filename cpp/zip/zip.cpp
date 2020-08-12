#include <iostream>
using namespace std;

#include "compress.h"

int main()
{
    // const char *filenames[] = {"tmp"};
    // const char *zip_filename = "foo.zip";
    // auto zip = zip_open("foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    // auto zip = zip_open("foo.zip", 9, 'w');
    // {
    //     write_file_with_dir(zip , "tmp/foo1.txt");
    //     write_file_with_dir(zip , "tmp/foo2.txt");
    //     write_file_with_dir(zip , "tmp/foo3.txt");
    // }
    // zip_close(zip);
    // zip_create(zip_filename, filenames, sizeof(filenames)/sizeof(*filenames));
    try {
        Compress compress("build.zip", 6, 'w');
        compress.append_dir("build");
        compress.compress();
        // 解压
        UnCompress uncompress("build.zip", "unbuild");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}
