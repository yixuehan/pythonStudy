#include <boost/timer/timer.hpp>
#include <string_view>
#include <boost/utility/string_view.hpp>
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    int const times = 100000;
    {
        std::string str{"foobar"};
        std::string bar;
        boost::timer::auto_cpu_timer t;
        for (int i = 0; i < times; ++i) {
            bar = str.substr(3);
        }
        assert(bar == "bar");
        //cout << "str:" << str << "\n";
    }
    {
        const std::string str{"foobar"};
        boost::string_view bar;
        boost::timer::auto_cpu_timer t;
        for (int i = 0; i < times; ++i) {
            //bar = boost::string_view{str.c_str(), str.size()};
            bar = boost::string_view{str.c_str(), str.size()};
            bar.remove_prefix(3);
        }
        assert(bar == "bar");
    }
}
