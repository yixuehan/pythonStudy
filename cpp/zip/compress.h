#pragma once
#include <string>
#include <vector>
#include <memory>

class ZipException : public std::exception
{
public:
    ZipException(const std::string &msg)
        :_msg(msg)
    {
    }
    const char *what() const noexcept
    {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

struct zip_t;

class Compress
{
public:
    Compress(const std::string &zip_filename, int level, char mode);
    ~Compress();
    void append_dir(const std::string &dirname);
    void append_file(const std::string &filename);
    void compress();
private:
    std::string _zip_filename;
    int _level;
    char _mode;
    std::vector<std::string> _dir_list;
    std::vector<std::string> _file_list;
private:
    void compress_file(std::shared_ptr<zip_t> zip_ptr, const std::string &filename);
    void close();
};

class UnCompress
{
public:
    UnCompress(const std::string &zip_filename, const std::string &target_dirname);
private:
    void unCompress();
private:
    std::string _zip_filename;
    std::string _target_dirname;
};
