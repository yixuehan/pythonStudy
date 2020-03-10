#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace boost::interprocess;


int main()
{
    try {
        shared_memory_object obj2(open_or_create, "name4", read_write);
        mapped_region region2(obj2, read_only);
        obj2.truncate(12345);
        auto raddr = region2.get_address();
        cout << (const char*)raddr << endl;
        getchar();
    }
    catch (boost::interprocess::interprocess_exception &e) {
        cout << e.what() << endl;
        shared_memory_object::remove("name4");
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
    shared_memory_object::remove("name4");
}
