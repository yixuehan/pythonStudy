#include <iostream>
#include <vector>
#include <string>
using namespace std;


/*
template < typename T, typename ... Ts >
void printf3(T &&value, Ts &&... args)
{
    cout << value << ' ';
    if constexpr(sizeof...(args) > 0) {
        printf3(std::forward<Ts>(args)...);
    }
}
*/

template < typename ... Ts >
auto printf3(Ts &&... args) ->void
{
       // std::cout << value << std::endl;
    
    int i = 0;
    std::initializer_list <int> {([](int &x, auto arg) {
            ++x;
            std::cout << x << ":" <<  arg << std::endl;
            return x;
    }(i, args), 0) ...};

}

void test_lambda()
{
 printf3(1, 2, 3.12);
}

template <typename T, int N = sizeof(T)>
void to_number(const string &, T &t);

template <>
void to_number(const string &str, int &r)
{
    r = stoi(str);
}

template <>
void to_number(const string &str, float &r)
{
    r = stof(str);
}

template <>
void to_number(const string &str, double &r)
{
    r = stof(str);
}

template <typename T, size_t N>
void to_number(const string &str, T(&ch)[N])
{
    cout << "r size:" << N << " " << str << ":" << sizeof(ch) << endl;
}


#include <boost/algorithm/string.hpp>
template <typename ... Args>
void str2var(string str, Args &...args)
{
    std::vector<string> ress;
    boost::split(ress, str, boost::is_any_of(","));
    int i = 0;
    std::initializer_list<int> {
        ([](auto &ress, int &i, auto &arg){ 
         to_number(ress[i], arg);
         ++i;
        }(ress, i, args), 0)...
    };
}

template <typename Char, typename ... Args>
void printPairs(std::pair<Char, Args&> ...ps)
{
    std::initializer_list<int> {
        ([](auto &p){
            p.second = 100;
         }(ps), 0)...
    };
}

struct Util
{
    Util(){}
    template <typename T>
    Util &operator()(const string &str, T &t)
    {
        printPairs(std::pair<std::string, T&>(str, t));
        return *this;
    }
};

int main()
{
    // test_lambda();
    int a, c;
    double b, d;
    char ch[20];
    str2var("10,20.43,321,443.132,abcdef", a, b, c, d, ch);
    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << endl;
    // std::pair<string, int&> p1("name"s, a);
    Util()("name"s, a)("name2", b);
    cout << a << ":" << b << endl;
}
