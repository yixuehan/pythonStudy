#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

#include "tree.h"


template <typename Key, typename Value>
struct AVLNode : public BaseNode<Key, Value>
{
};

template <typename Key, typename Value, typename Node = AVLNode<Key, Value>>
class AVLTree : public BaseTree<Key, Value, Node>
{
public:
    using Iterator = typename BaseTree<Key, Value, Node>::Iterator;
public:
    AVLTree()
    {
    }
    Iterator Insert(const Key &key, const Value &value)
    {
        if (!this->_root) {
            this->_root = new Node(key, value);
            return Iterator(this->_root);
        }
        return this->_end;
        // return _end;
    }
};

int main()
{
}
