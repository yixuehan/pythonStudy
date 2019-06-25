#include <iostream>
#include <array>
#include <vector>
#include <stack>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

#include "way.h"

std::vector<Way> min_path(const Way &start)
{
    std::stack<Way> ways;
    std::vector<Way> result;
    // for (auto &start : starts)
    ways.push(start);
    while (!ways.empty()) {
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

    // Way way1(m, m.start, Up);
    // Way way2(m, m.start, Down);
    // Way way3(m, m.start, Left);
    // Way way4(m, m.start, Right);
    Way start(m, m.start);
    // auto ress = min_path({way1, way2, way3, way4});
    auto ress = min_path(start);
    for (auto &res : ress) {
        for (auto &pos : res.passed()) {
            cout << pos;
        }
        cout << endl;
    }

}
