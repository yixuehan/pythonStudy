#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    FILE *fp = fopen("data.dat", "wb");
    char buffer[100] = "abcdef";
    fwrite(buffer, 1, strlen(buffer), fp);
    sleep(100);
    // cout << buffer << endl;
}
