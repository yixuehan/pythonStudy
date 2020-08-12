#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

#include <fmt/format.h>

int main()
{
    string cmd = "{} {}";
    cmd = fmt::format(cmd, 10);
    cout << cmd << endl;
    // cmd = fmt::format(cmd, 20);
    // cout << cmd << endl;
}
