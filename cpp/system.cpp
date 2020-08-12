#include <thread>
#include <iostream>
#include <system_error>
 
int main()
{
    try {
        std::thread().detach(); // 试图脱附一个非线程
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code() 
                  << " meaning " << e.what() << '\n';
    }
}
