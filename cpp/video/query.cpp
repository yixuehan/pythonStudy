#include <iostream>
using namespace std;

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

void query_info(const char *filename)
{
    printf("%s info:\n", filename);
    int fd = open(filename, O_RDWR);
    v4l2_capability cap;
    ioctl(fd, VIDIOC_QUERYCAP, &cap);
    printf("DriverName:%s\nCard Name:%s\nBus info:%s\nDriverVersion:%u.%u.%u\n\n", 
            cap.driver, cap.card, cap.bus_info, (cap.version>>16)&0XFF, (cap.version>>8)&0XFF, cap.version&0XFF);


    close(fd);
}

void query_video()
{
    char buf[128] = {0};
    FILE *fp = popen("gst-device-monitor-1.0  | grep device.path", "r");
    while (fgets(buf, sizeof(buf), fp)) {
        printf("%s", buf);
    }

    pclose(fp);
}

int main()
{
    // query_info("/dev/video0");
    // query_info("/dev/video1");
    query_video();
}
