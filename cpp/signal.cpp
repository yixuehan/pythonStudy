#include <iostream>
#include <fstream>

#include <signal.h>
#include <unistd.h>

std::ofstream ofs("sig.txt");
bool bEnd = false;

void sigint(int x)
{
    ofs << x << "\n";
    ofs << std::flush;
    bEnd = true;
}

int main()
{
    //sigset_t set;
    for ( int i = 1;i <= 64; ++i ) {
        if (SIG_ERR == signal(i, sigint)) {
            ofs << "捕获信号失败:" << i << "\n";
            if (SIG_ERR == signal(i, SIG_IGN)) {
                ofs << "忽略信号失败:" << i << "\n";
            }
        }
        //sigaddset(&set, i);
    }
    ofs << std::flush;

    while(!bEnd);
    sleep(2);
    ofs << "end\n";
}
