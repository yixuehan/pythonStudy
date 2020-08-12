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
        shared_memory_object obj1(open_or_create, "name4", read_write);
        obj1.truncate(12345);
        mapped_region region1(obj1, read_write);
        auto addr = region1.get_address();
        strcpy((char*)addr, "hello world");
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
