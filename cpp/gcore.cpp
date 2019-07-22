#include <unistd.h>

#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    char buf[64]{};
    sprintf(buf, "gcore %d", getpid());
    system(buf);
    sprintf(buf, "cat /proc/%d/exe > progma.%d", getpid(), getpid());
    system(buf);
    a = 20;
    printf("a = %d\n", a);
    getchar();
}
