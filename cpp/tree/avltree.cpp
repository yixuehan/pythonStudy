#include <iostream>
#include <vector>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

template <typename Value>
struct AVLNode
{
    AVLNode(Value value)
        :father(nullptr),
         left(nullptr),
         right(nullptr),
         next(nullptr),
         height_left(0),
         height_right(0),
         data(value)
    { 
    } 
    AVLNode *father;
    AVLNode *left;
    AVLNode *right;
    AVLNode *prev;
    AVLNode *next;
    int height_left;
    int height_right;
    Value data;
    
    // std::pair<KeyType, ValueType> data;
};


constexpr int screen_width = 180;
// constexpr int interval = 3;

template <typename Value, typename Node = AVLNode<Value>>
class AVLTree
{
public:
    class Iterator;
    // using Iterator = typename AVLTree<Value>::Iterator;
public:
    AVLTree()
        :_root{nullptr},
         _begin{nullptr},
         _end{nullptr}

    {
    }
    Iterator insert(const Value &value)
    {
        if (!this->_root) {
            this->_root = new Node(value);
            _begin = Iterator(this->_root);
            return _begin;
        }
        return insert(_root, value);
        // return _end;
    }
    struct NodeInfo
    {
        int pos;
        Node *node;
    };
    void pre_order()
    {
        pre_order(_root);
        printf("\n");
    }
    void pre_order(Node *node)
    {
        if (!node) return;
        pre_order(node->left);
        printf("%d ", node->data);
        pre_order(node->right);
    }

    void pos_print(const vector<NodeInfo> &values)
    {
        size_t i = 0;
        for (int i = 0; i < values.size(); ++i) {
            int left = -1, right = -1;
            if (values[i].node->left) left = values[i].node->left->data;
            if (values[i].node->right) right = values[i].node->right->data;
            printf("%d[%d:%d]", values[i].node->data, left, right);
            // printf("[%d:%d]", values[i].pos, values[i].node->data);
        }
        printf("\n\n");
        return ;
        
        for (int pos = 0; pos < screen_width; ++pos) {
            if (i >= values.size()) {
                break;
            }
            if (pos == values[i].pos) {
                int left = -1, right = -1;
                if (values[i].node->left) left = values[i].node->left->data;
                if (values[i].node->right) right = values[i].node->right->data;
                printf("%d[%d:%d]", values[i].node->data, left, right);
                ++i;
            }
            else {
                printf(" ");
            }
        }
        printf("\n\n");
    }

    void print()
    {
        print(vector<NodeInfo>{NodeInfo{screen_width / 2, _root}}, 15);
    }
    void print(vector<NodeInfo> node_infos, int interval)
    {
        // vector<vector<NodeInfo>> ;
        // NodeInfo node_info{screen_width / 2, node};
        if (0 == node_infos.size()) return;
        vector<NodeInfo> children;
        pos_print(node_infos);
        for ( auto &node_info : node_infos) {
            Node *left = node_info.node->left;
            Node *right = node_info.node->right;
            if (left) {
                children.push_back({node_info.pos - interval, left});
            }
            
            if (right) {
                children.push_back({node_info.pos + interval, right});
            }
        }
        return print(children, interval - 4);
    }
private:
    Node *ll_rotate(Node *node)
    {
        Node *_new = node->left;
        node->left = _new->right;
        _new->right = node;
        return _new;
        // node = _new;
        // return _new;
    }

    Node *rr_rotate(Node *node)
    {
        Node *_new = node->right;
        node->right = _new->left;
        _new->left = node;
        return _new;
        // node = _new;
    }

    Node *lr_rotate(Node *node)
    {
        // 转成ll
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }

    Node *rl_rotate(Node *node)
    {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }

    int height(Node *node)
    {
        if (!node) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }

public:
    class Iterator
    {
    public:
        Iterator (Node *node)
            :_node(node)
        {}
        Iterator &operator++(int)
        {
            _node = _node->next;
            return *this;
        }
        Iterator &operator--(int)
        {
            _node = _node->prev;
            return *this;
        }
        Value &operator*()
        {
            return _node->data;
        }
        Value &operator->()
        {
            return **this;
        }
    private:
        Node *_node;
    };
private:
    Node *_root;
    Iterator _begin;
    Iterator _end;
private:
    // void reblance(Node *&node)
    // {
    // }
    Iterator insert(Node *&node, const Value &data)
    {
        Iterator iter(nullptr);
        if (!node) {
            node = new Node(data);
        }
        else if (data == node->data) {
            return Iterator(node);
        }
        else if (data < node->data) {
            iter = insert(node->left, data);
            if ((height(node->left) - height(node->right)) > 1) {
                if (data < node->left->data) {
                    node = ll_rotate(node);
                }
                else {
                    node = lr_rotate(node);
                }
            }
        }
        else {
            iter = insert(node->right, data);
            if ((height(node->right) - height(node->left)) > 1) {
                if (data > node->right->data) {
                    node = rr_rotate(node);
                }
                else {
                    node = rl_rotate(node);
                }
            }
        }
        return iter;
    }
};

int main()
{
    AVLTree<int> t;
    srand(time(nullptr));
    for (int i = 0; i < 1000; ++i) {
        t.insert(rand() % 1000);
    }
    t.pre_order();
    t.print();
}
