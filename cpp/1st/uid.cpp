#include <unistd.h>
#include <sys/types.h>

#include <iostream>
using namespace std;

int main()
{
    cout << getuid() << ' ' << getgid() << endl;
}
