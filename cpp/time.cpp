#include <iostream>
#include <chrono>
#include <unistd.h>
using namespace std;

int main()
{
    //auto nano = chrono::steady_clock::now().time_since_epoch();
    while(1) {
        auto nano = chrono::high_resolution_clock::now().time_since_epoch();
        //auto nano = chrono::system_clock::now().time_since_epoch();
        //chrono::system_clock clock;

        cout << chrono::system_clock::is_steady << endl;

        auto mill = chrono::duration_cast<chrono::milliseconds>(nano);

        auto micro = chrono::duration_cast<chrono::microseconds>(nano);

        auto sec = chrono::duration_cast<chrono::seconds>(nano);

        cout << nano.count() << endl;

        cout << micro.count() << endl;

        cout << mill.count() << endl;

        cout << sec.count() << endl;

        sleep(1);
    
    }
}
