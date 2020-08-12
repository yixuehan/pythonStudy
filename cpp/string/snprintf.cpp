#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    char buff[8];
    snprintf(buff, sizeof(buff), "%s", "12345678");
    printf("%c %c\n", buff[6], buff[7]);
}
