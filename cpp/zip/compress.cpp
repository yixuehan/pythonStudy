#include "compress.h"
#include <zip/zip.h>
#include <iostream>
using namespace std;

#include <boost/filesystem.hpp>


struct zip_t;

vector<string> get_all_files(const string &dirname)
{
    using namespace boost;
    vector<string> file_list;
    try {
        for (auto &p: filesystem::recursive_directory_iterator(dirname)) {
            if (!filesystem::is_directory(p.status())) {
                file_list.push_back(p.path().string());
            }   
        }
    }
    catch (std::exception &e) {
        throw ZipException(string("压缩目录失败:") + e.what());
    }
    return file_list;
}

Compress::Compress(const std::string &zip_filename, int level, char mode)
    :_zip_filename(zip_filename)
    ,_level(level)
    ,_mode(mode)
{
}

Compress::~Compress()
{
}

void Compress::append_dir(const std::string &dirname)
{
    _dir_list.push_back(dirname);
}

void Compress::append_file(const std::string &filename)
{
    _file_list.push_back(filename);
}

void Compress::compress()
{
    std::shared_ptr<zip_t> zip_ptr(zip_open(_zip_filename.c_str(), _level, _mode),
        [](zip_t *p)
            {
                zip_close(p);
            });
    if (!zip_ptr) {
        throw ZipException("创建压缩文件失败：" + _zip_filename);
    }
    for (auto &filename : _file_list) {
        compress_file(zip_ptr, filename);
    }
    for (auto &dirname : _dir_list) {
        auto all_files = get_all_files(dirname);
        for (auto &filename : all_files) {
            compress_file(zip_ptr, filename);
        }
    }
}

void Compress::compress_file(std::shared_ptr<zip_t> zip_ptr, const std::string &filename)
{
    if (!zip_ptr) {
        throw ZipException("压缩文件尚未创建:" + _zip_filename);
    }
    if (0 > zip_entry_open(zip_ptr.get(), filename.c_str())) {
        throw ZipException("创建压缩档案失败:" + filename);
    }
    if (0 > zip_entry_fwrite(zip_ptr.get(), filename.c_str())) {
        throw ZipException("添加压缩档案失败:" + filename);
    }
    if (0 > zip_entry_close(zip_ptr.get())) {
        throw ZipException("关闭压缩档案失败:" + filename);
    }
}

UnCompress::UnCompress(const std::string &zip_filename, const std::string &target_dirname)
    :_zip_filename(zip_filename)
    ,_target_dirname(target_dirname)
{
    unCompress();
}

void UnCompress::unCompress()
{
    if (0 > zip_extract(_zip_filename.c_str(), _target_dirname.c_str(), nullptr, nullptr)) {
        throw ZipException("解压失败[" + _zip_filename + "]->[" + _target_dirname + "]");
    }
}
