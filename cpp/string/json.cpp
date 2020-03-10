#include <iostream>
using namespace std;

// #include <boost/timer/timer.hpp>
// using namespace boost;

#include <nlohmann/json.hpp>

struct B
{
    int x ;
    string c;
};

inline void to_json(nlohmann::json &j, const B &b)
{
    j["x"] = b.x;
    j["c"] = b.c;
}


struct A
{
    int a;
    string b;
    B c;
};

inline void from_json(const nlohmann::json &j, A &a)
{
    j.at("a").get_to(a.a);
    j.at("b").get_to(a.b);
    string c = j["c"];
    j.at("c").get_to(c);
}

inline void to_json(nlohmann::json &j, const A &a)
{
    j["a"] = a.a;
    j["b"] = a.b;
    to_json(j, a.c);
}

int main()
{
    nlohmann::json j = nlohmann::json::parse(
            R"({
    "a": 100,
    "a": "hello",
    "b": "hello",
    "c": "world",
    "x": 200
})");
    cout << j.dump(4) << "\n";
    j["self"] = 100;
    cout << j.dump(4) << "\n";
    A a;
    a.a = 100;
    a.b = "hello";
    a.c.x = 200;
    a.c.c = "world";
    to_json(j, a);
    cout << j.dump(4) << "\n";
    vector<char> ch_list{'a', 'b', 'c'};
        j["a"] = 10;
        j["b"] = "str b";
        // j["c"]["d"] = 100;
        // j["c"]["d"] = "中文";
        j["ch_list"] = ch_list;
        a = j;
        cout << j << endl;
        cout << a.a << ' ' << a.b << endl;
        string str;
        j.at("abc").get_to(str);
    cout << R"((((((()))))))" << endl;
    // int a;
    // j.at("100").get_to(a);
}
