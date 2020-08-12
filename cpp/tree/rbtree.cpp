#include "tree.h"
using namespace std;

constexpr byte RED = byte(0);
constexpr byte BLACK = byte(1);

template <typename V>
struct TNode
{
    TNode(V value, byte color)
        :father(nullptr),
         left(nullptr),
         right(nullptr),
         next(nullptr),
         data(value),
         color(color)
    {
    }
    TNode *father;
    TNode *left;
    TNode *right;
    TNode *next;
    using ValueType = V;
    ValueType data;
    byte color;
};

template <typename K, typename V>
class RBTree
{
public:
    RBTree()
        :_root(V{}, BLACK),
         _nil(V{}, BLACK)
    {
    }
    RBTree(const RBTree &o)
        :_root(o._root),
         _nil(o._nil)
    {
    }
    V &operator[](const K &k)
    {
    }
private:
    TNode<V> _root;
    TNode<V> _nil;
private:
};

int main()
{
}
