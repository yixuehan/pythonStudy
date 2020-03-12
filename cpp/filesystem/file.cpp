#include <sys/stat.h>

#include <iostream>
#include <filesystem>
using namespace std;

//#include <boost/filesystem.hpp>
#include <boost/format.hpp>

void printFileStat(char const* filename)
{
    cout << "****************************************" << filename << "************************************\n";
    struct stat file_stat;
    stat(filename, &file_stat);
    boost::format fmt("mode:%o\n"
                      "ino:%d\n"
                      "dev:%d\n"
                      "rdev:%d\n"
                      "nlink:%d\n"
                      "uid:%d\n"
                      "gid:%d\n"
                      "size:%lu\n"
                      "atime:%lu\n"
                      "mtime:%lu\n"
                      "ctime:%lu\n"
                      "blksize:%lu\n"
                      "blocks:%lu\n");
    fmt % file_stat.st_mode
        % file_stat.st_ino
        % file_stat.st_dev
        % file_stat.st_rdev
        % file_stat.st_nlink
        % file_stat.st_uid
        % file_stat.st_gid
        % file_stat.st_size
        % file_stat.st_atime
        % file_stat.st_mtime
        % file_stat.st_ctime
        % file_stat.st_blksize
        % file_stat.st_blocks
        ;
    cout << fmt.str();

    cout << S_ISREG(file_stat.st_mode) << endl
         << S_ISDIR(file_stat.st_mode) << endl
         << S_ISCHR(file_stat.st_mode) << endl
         << S_ISBLK(file_stat.st_mode) << endl
         << S_ISFIFO(file_stat.st_mode) << endl
         << S_ISLNK(file_stat.st_mode) << endl
         << S_ISSOCK(file_stat.st_mode) << endl
         ;
}

void printStat(char const *filename)
{
    namespace fs = std::filesystem;
    cout << "--------------------filesystem:" << filename << "----------------------\n";
    fs::path p(filename);
    cout << fs::is_directory(p) << endl;
    auto st = fs::status(p);
    if (fs::is_socket(st)){
        cout << "socket file\n";
    }
    else if (fs::is_block_file(st)) {
        cout << "block file\n";
    }

}

namespace fs = std::filesystem;
int main()
{
    printFileStat("./a.out");
    printFileStat("/dev/log");
    printFileStat("/dev/stderr");
    printFileStat("/dev/stderr");
    printFileStat("/dev/sda");
    printFileStat("/dev/tty0");
    printFileStat(".");
    printStat(".");
    printStat("a.out");
    printStat("/dev/log");
    cout << fs::current_path() << endl;
    auto path = fs::current_path();
    auto path2 = path / "./dir1" / "a.json";
    cout << path << endl;
    cout << path2 << endl;
    cout << fs::current_path() << endl;
}
