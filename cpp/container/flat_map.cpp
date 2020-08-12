#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/container/flat_set.hpp>
using namespace boost;

constexpr size_t NUM = 100000;

#include <stdlib.h>

template <typename T>
void print(const T &nums)
{
    return;
    for (auto iter = std::begin(nums); iter != std::end(nums); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
}

int main()
{
    srand(time(0));
    set<int> s1;
    container::flat_set<int> s2;
    int s3[NUM];
    unordered_set<int> s4;
    {
        timer::auto_cpu_timer t;
        for (size_t i = 0; i < NUM ; ++i) {
            s1.insert(rand());
        }
        cout << "set:";
        print(s1);
    }
    {
        timer::auto_cpu_timer t;
        for (size_t i = 0; i < NUM ; ++i) {
            s2.insert(rand());
        }
        cout << "flat_set:";
        print(s2);
    }
    {
        timer::auto_cpu_timer t;
        for (size_t i = 0; i < NUM ; ++i) {
            s3[i] = (rand());
        }
        std::sort(std::begin(s3), std::end(s3));
        cout << "array:";
        print(s3);
    }
    {
        timer::auto_cpu_timer t;
        for (size_t i = 0; i < NUM ; ++i) {
            s4.insert(rand());
        }
        cout << "unordered_set:";
        print(s4);
    }
}
