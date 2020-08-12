#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    auto res = split("adopaow,aowpjf,doiwpfj,aoiw,wpwf,", ',');
    for (auto &r : res) {
        cout << r << endl;
    }
}
