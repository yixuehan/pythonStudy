#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
#include <iterator>
#include <cstdlib> 

using namespace boost::interprocess;
using namespace std::literals;

int main(int argc, char* argv[])
{
	if (argc == 1)
    { 
        shared_memory_object::remove("MySharedMemory");
		managed_shared_memory segment(create_only, "MySharedMemory", 65534);
		auto* myvector = segment.construct<string>("String")("123456789012345678901");
        myvector->append("2"); //

		std::string s(argv[0]); s += " child ";
		if (0 != std::system(s.c_str()))
			return 1;
		if (segment.find<string>("String").first)
			return 1;
	}
	else {
		managed_shared_memory segment(open_only, "MySharedMemory");
		std::pair<string*, std::size_t> p = segment.find<string>("String");
		std::cout << *p.first << std::endl;
		segment.destroy<string>("String");
	}

	return 0;
}
