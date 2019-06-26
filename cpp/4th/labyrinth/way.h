#pragma once
#include "assert.h"

#include <set>

#include "pos.h"
#include "labmap.h"

class Way
{
public:
    Way(const Labmap &m,
        const Pos &curr
        )
        :_map{m},
         _curr{curr},
         _steps{0}
    {
        _passed.insert(_curr);
        _passed_array.push_back(_curr);
    }

    Way(const Way &th)
        :Way(th._map, th._curr)
    {
        _passed = th._passed;
        _passed_array = th._passed_array;
        _steps = th._steps;
    }

    int steps() const
    {
        return _steps;
    }

    const std::vector<Pos>& passed() const
    {
        return _passed_array;
    }

    bool isArrived() const
    {
        return _map.labmap[_curr.x][_curr.y] == _map.target;
    }

    bool isValidPos(const Pos &pos) const {
        if (_map.labmap.size() == 0) return false;
        if (_map.labmap[0].size() == 0) return false;
        if (pos.x < 0 || pos.y < 0 
            || size_t(pos.x) >= _map.labmap.size()
            || size_t(pos.y) >= _map.labmap[0].size()
           )   
            return false;
    
        if (_map.labmap[pos.x][pos.y] == _map.barrier)
            return false;

        // if (_map.labmap[pos.x][pos.y] == _map.target)
        //     return false;

        if (_passed.find(pos) != _passed.end())
            return false;


        return true;
    }

    std::vector<Way> next() {
        std::vector<Way> result;
        for (auto &step : NextPosChoices) {
            auto next = _curr + step;
            if (isValidPos(next)) {
                auto temp(*this);
                temp._curr = next;
                temp._steps++;
                assert(temp._passed.insert(next).second);
                temp._passed_array.push_back(next);
                result.push_back(std::move(temp));
            }
        }
        return result;
    }

private:
    Labmap _map;
    Pos _curr;
    std::set<Pos> _passed;
    std::vector<Pos> _passed_array;
    int _steps;
};
