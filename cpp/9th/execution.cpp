#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <execution>
using namespace std;

int main()
{
    vector<int> v(1000000000);
    generate(begin(v), end(v), random());
}
