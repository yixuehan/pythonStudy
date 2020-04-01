#include <iostream>
using namespace std;

#include <muduo/net/EventLoop.h>


int main()
{
    muduo::net::EventLoop loop;
    loop.runEvery(1, []{
            printf("time out\n");
            });
    loop.loop();
}
