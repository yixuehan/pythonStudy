#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <iostream>
using namespace std;

int main()
{
    printf("uid = %u, gid = %u, euid = %u, egid = %u\n", getuid(), getgid(),
            geteuid(), getegid());
    int fd = open("a.txt", O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    close(fd);
}
