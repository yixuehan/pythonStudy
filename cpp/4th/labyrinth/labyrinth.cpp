#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

#include "way.h"

int maxway = 0;

std::vector<Way> min_path(const Way &start)
{
    std::stack<Way> ways;
    std::vector<Way> result;
    ways.push(start);
    while (!ways.empty()) {
        maxway = std::max<int>(maxway, ways.size());
        auto currway = ways.top();
        ways.pop();
        if (currway.isArrived()) {
            if (result.empty()) {
                result.push_back(currway);
            }
            else {
                if (result[0].steps() > currway.steps()) {
                    result.clear();
                    result.push_back(currway);
                }
                else if (result[0].steps() == currway.steps()) {
                    result.push_back(currway);
                }
            }
        }
        else {
            auto nexts = currway.next();
            for (auto &way : nexts) {
                ways.push(std::move(way));
            }
        }
    }
    return result;
}

int main()
{
    Labmap m;
    m.target = 2;
    m.barrier = 1;
    m.start = {0, 0};
    m.labmap = 
    {
     {0, 0, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 1, 0},
     {0, 1, 2, 0},
     {0, 0, 0, 1}
    };

    Way start(m, m.start);
    auto ress = min_path(start);
    for (auto &res : ress) {
        for (auto &pos : res.passed()) {
            cout << pos;
        }
        cout << endl;
    }
    cout << "max count:" << maxway << endl;

}
