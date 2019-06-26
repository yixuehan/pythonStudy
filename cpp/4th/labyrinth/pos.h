#pragma once
#include <iostream>
struct Pos
{
    int x;
    int y;
    bool operator==(const Pos &pos) const
    {   
        return x == pos.x && y == pos.y;
    }   
    Pos operator+(const Pos &pos) const
    {   
        return {x + pos.x, y + pos.y};
    }   
    bool operator<(const Pos &pos) const
    {
        return x < pos.x || (x == pos.x && y < pos.y);
    }
};

std::ostream &operator<<(std::ostream &os, const Pos &p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os; 
}

Pos Left{0, -1};
Pos Right{0, 1};
Pos Up{-1, 0};
Pos Down{1, 0};
Pos NextPosChoices[4] = {Left, Right, Up, Down};

