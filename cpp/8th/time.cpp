#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;

ostream& operator<<(ostream &os,
    const chrono::time_point<chrono::system_clock> &t)
{
    const auto tt (chrono::system_clock::to_time_t(t));
    const auto loct (std::localtime(&tt));
    return os << put_time(loct, "%c");
}

using days = chrono::duration<
    chrono::hours::rep,
    ratio_multiply<chrono::hours::period, ratio<24>>>;

constexpr days operator ""_days(unsigned long long h)
{
    return days{h};
}

int main()
{
    auto now (chrono::system_clock::now());

    cout << "The current date and time is " << now << '\n';
}
