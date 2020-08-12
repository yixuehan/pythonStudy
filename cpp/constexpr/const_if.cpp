#include <iostream>
using namespace std;

int main()
{
    if constexpr(true) {
        printf("true\n");
    }
    else {
        static_assert(false, "false");
    }
}
