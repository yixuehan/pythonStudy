#include <iostream>
using namespace std;

class StringLiteral
{
public:
    StringLiteral() = default;
    StringLiteral(const char* str) : _str(str) {}

    void print(int x = 10)
    {
        x = 10;
    }

    friend std::ostream& operator<<(std::ostream& os, const StringLiteral& s)
    {   
        return os << s._str;
    }   

    ~StringLiteral() = default;

private:
    int a;
    const char* _str;
};
static_assert(std::is_pod<StringLiteral>::value, "StringLiteral must be POD.");

int main()
{
}
