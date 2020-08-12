#include <signal.h>
#include <unistd.h>

#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

void sighandle(int sighandle)
{
    switch (sighandle) {
    case SIGSEGV:
        cout << "sigsegv" << endl;
        char buf[32] = {0};
        sprintf(buf, "gcore %d", getpid());
        signal(SIGSEGV, SIG_DFL);
        system(buf);
        cout << "done" << endl;
    }
}

int main()
{
    signal(SIGSEGV, sighandle);
    int *pa = nullptr;
    *pa = 10;
}
