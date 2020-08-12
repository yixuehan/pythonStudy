#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;

struct FileInfoHeader
{
    int command;
    string deviceId;
    string from;
    string path;
};


void to_json(nlohmann::json &j, const FileInfoHeader &h)
{
    j = nlohmann::json {
        {"command", h.command},
        {"deviceId", h.deviceId},
        {"from", h.from},
        {"path", h.path},
    };
}

struct FileInfo
{
    string createTime;
    bool isDir;
    string modifyTime;
    string fileName;
    string filePath;
    int fileSize;
    string fileType;
    string visitTime;
};

void to_json(nlohmann::json &j, const FileInfo &info)
{
    j = nlohmann::json {
        {"createTime:", info.createTime},
        {"isDir:", info.isDir},
        {"modifyTime:", info.modifyTime},
        {"filename:", info.fileName},
        {"filePath:", info.filePath},
        {"fileSize:", info.fileSize},
        {"fileType:", info.fileType},
        {"visitTime:", info.visitTime},
    };
}

struct FileInfoRequest
{
    FileInfoHeader header;
    std::vector<FileInfo> fileInfoList;
};

void to_json(nlohmann::json &j, const FileInfoRequest &req)
{
    j = nlohmann::json {
        {"request", req.header},
        {"result", req.fileInfoList},
    };
}

void printFileInfo(const FileInfo &f)
{
    // cout << nlohmann::json(f).dump(4);
    return;
    cout << "create time:" << f.createTime << "\n"
         << "is dir:" << f.isDir << "\n"
         << "modify time:" << f.modifyTime << "\n"
         << "filename:" << f.fileName << "\n"
         << "file path:" << f.filePath << "\n"
         << "file size:" << f.fileSize << "\n"
         << "file type:" << f.fileType << "\n"
         << "visit time:" << f.visitTime << "\n\n";
}

string str_time(time_t t)
{
    auto tm = localtime(&t);
    char buf[32] = {};
    sprintf(buf, "%d-%d-%d %d:%d:%d",
            tm->tm_year + 1900,
            tm->tm_mon + 1,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec
            );
    // printf("str_time:%s\n", buf);
    return string(buf);
}

string fileType(int file_type)
{
    if (S_ISDIR(file_type)) {
        return "dir";
    }
    if (S_ISBLK(file_type)) {
        return "block";
    }
    if (S_ISCHR(file_type)) {
        return "char";
    }
    if (S_ISREG(file_type)) {
        return "file";
    }
    if (S_ISSOCK(file_type)) {
        return "socket";
    }
    if (S_ISLNK(file_type)) {
        return "link";
    }
    if (S_ISFIFO(file_type)) {
        return "fifo";
    }
    return "unknown";
}

vector<FileInfo> dirList(const std::string &path)
{
    vector<FileInfo> fileInfoList;
    auto dp = opendir(path.c_str());
    for (auto item = readdir(dp); item; item = readdir(dp)) {
        struct FileInfo info{};
        auto abs_filename = path + "/" + item->d_name;
        info.fileName = item->d_name;
        struct stat file_stat;
        stat(abs_filename.c_str(), &file_stat);

        info.createTime = str_time(file_stat.st_ctime);
        info.isDir = S_ISDIR(file_stat.st_mode);
        info.modifyTime = str_time(file_stat.st_mtime);
        info.filePath = path;
        info.fileSize = file_stat.st_size;
        info.fileType = fileType(file_stat.st_mode);
        info.visitTime = str_time(file_stat.st_atime);

        printFileInfo(info);
        fileInfoList.push_back(info);
    }
    return fileInfoList;
}



int main()
{
    FileInfoRequest req;
    auto &h = req.header;
    h.command = 0x1011;
    h.deviceId = "dowiwofj";
    h.from = "/home/shenlan";
    h.path = "/home/shenlan";
    req.fileInfoList = dirList("/home/shenlan");
    nlohmann::json j = req;
    cout << "req:" << j.dump(4) << endl;
}
