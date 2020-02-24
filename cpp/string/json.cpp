#include <iostream>
using namespace std;

// #include <boost/timer/timer.hpp>
// using namespace boost;

#include <nlohmann/json.hpp>

struct A
{
    int a;
    string b;
};

inline void from_json(const nlohmann::json &j, A &a)
{
    j.at("a").get_to(a.a);
    j.at("b").get_to(a.b);
    string c = j["c"];
    j.at("c").get_to(c);
}

int main()
{
    nlohmann::json::parse("{}");
    nlohmann::json j;
    try {
        j["a"] = 10;
        j["b"] = "str b";
        // j["c"]["d"] = 100;
        j["c"]["d"] = "中文";
        A a = j;
        cout << j << endl;
        cout << a.a << ' ' << a.b << endl;
        string str;
        j.at("abc").get_to(str);
    }
    catch (...) {
        cout << "exception";
    }
    int a;
    j.at("100").get_to(a);
}
