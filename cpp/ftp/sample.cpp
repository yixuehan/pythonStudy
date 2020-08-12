#include "ftplib.h"
#include <iostream>
#include <filesystem>
using namespace std;


bool path_exists(ftplib *ftp, const char *path)
{
    char old_path[512] = {0};
    ftp->Pwd(old_path, sizeof(old_path));
    int r = ftp->Chdir(path);
    ftp->Chdir(old_path);
    return r == 1;
}

void mkdirs(ftplib *ftp, const char *path)
{
    auto p = filesystem::path(path);
    if (path_exists(ftp, p.c_str())) {
        return;
    }
    else {
        mkdirs(ftp, p.parent_path().c_str());
        ftp->Mkdir(path);
    }
}

int main(void)
{
	ftplib *ftp = new ftplib();
	ftp->Connect("10.16.35.133:21");
	ftp->Login("middle_dev", "deepblue2020");
	int r = ftp->Chdir("/dev/a/b");
    cout << "r = " << r << endl;
    mkdirs(ftp, "/dev/x/y/z");
	ftp->Quit();
    delete ftp;
	return 0;
}
