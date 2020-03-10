#include <iostream>
#include <string_view>
#include <regex>
#include <bitset>

using namespace std;

int main()
{
    string_view view = "严好abc\u0001\n";
    for (auto c : view) {
        printf("%hhx ", c);
    }
    printf("\n");
    for (auto c : view) {
        bitset<8> bit(c);
        cout << bit.to_string() << " ";
    }
    cout << "\n";
}
