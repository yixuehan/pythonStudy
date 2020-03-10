#include <iostream>
#include <vector>
using namespace std;

class StringLiteral
{
public:
    StringLiteral() = default;
    // StringLiteral(){}
    StringLiteral(const char* str) : _str(str) {}

    void print(int x = 10)
    {
        x = 10;
    }

    friend ostream& operator<<(ostream& os, const StringLiteral& s)
    {   
        return os << s._str;
    }   

    ~StringLiteral() = default;

private:
    int a;
    const char* _str;
};

static_assert(is_pod<StringLiteral>::value, "StringLiteral must be POD.");

struct A
{
    // A(){}
    template <typename T>
    operator T()
    {
        return T();
    }
    int a;
    int *p;
    A &operator =(char c)
    {
        return *this;
    }
};

struct B : public A
{
    B() = default;
};

static_assert(is_pod<A>::value, "struct A must bo POD");
static_assert(is_pod<B>::value, "struct B must bo POD");
// static_assert(is_pod<vector<int>>::value, "vector<int> must bo POD");

int main()
{
    A a;
    B b = a;
    if constexpr(is_pod<vector<int>>::value) {
        cout << "vector<int> is pod\n";
    } {
        cout << "vector<int> is not pod\n";
    }
}
