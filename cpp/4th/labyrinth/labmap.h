#pragma once
#include "pos.h"
#include <vector>

struct Labmap
{
    Pos start;
    int target;
    int barrier;
    std::vector<std::vector<int>> labmap;
};
