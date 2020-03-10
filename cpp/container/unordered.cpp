#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

// #include <boost/timer/timer.hpp>
// using namespace boost;

template < typename Map>
class MyMap
{
    using K = typename Map::key_type;
    using V = typename Map::value_type;
    using Vector = vector<typename Map::key_type>;
    using value_type = typename Map::iterator::value_type;
public:
    struct iterator : public Map::iterator
    {
        iterator(Vector &v, Map &m, size_t pos)
            :_v(v),
             _m(m),
             _pos(pos)
        {
        }
        Vector &_v;
        Map &_m;
        size_t _pos;
        value_type operator*()
        {
            return value_type{_v[_pos], _m[_v[_pos]]};
        }

        bool operator!=(const iterator &r) const
        {
            return _pos != r._pos;
        }
        iterator &operator++()
        {
            _pos++;
            return *this;
        }
    };
    auto begin()
    {
        return iterator(_keys, _m, 0);
    }

    auto end()
    {
        return iterator(_keys, _m, _keys.size());
    }

    auto insert(const pair<K, V> &p)
    {
        auto r = _m.insert(p);
        if (r.second) {
            _keys.push_back(r.first);
        }
        return r;
    }

    auto &operator[](const K &k)
    {
        if (_m.find(k) == _m.end()) {
            _keys.push_back(k);
        }
        return _m[k];
    }

private:
    Vector _keys;
    Map _m;
};

int main()
{
    MyMap<unordered_map<int, int>> om;
    om[100] = 20;
    om[30] = 20;
    om[50] = 20;
    om[20] = 20;
    om[90] = 20;
    om[60] = 20;
    om[70] = 20;
    for (auto [K, V] : om) {
        cout << K << ":" << V << endl;
    }
}
