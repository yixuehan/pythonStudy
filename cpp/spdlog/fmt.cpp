#include <iostream>
using namespace std;

#include <fmt/format.h>


int main()
{
    fmt::format("{:4d}", 10);
    fmt::print("{:010d}", 10);
}
