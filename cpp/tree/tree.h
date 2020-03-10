#pragma once
#include <iostream>
// using byte = unsigned char;

constexpr byte RED = byte(0);
constexpr byte BLACK = byte(1);

template <typename K, typename V>
struct BaseNode
{
    BaseNode(V value)
        :father(nullptr),
         left(nullptr),
         right(nullptr),
         next(nullptr),
         data(value)
    {
    }
    BaseNode *father;
    BaseNode *left;
    BaseNode *right;
    BaseNode *prev;
    BaseNode *next;

    using KeyType = K;
    using ValueType = V;

    std::pair<KeyType, ValueType> data;
};

template <typename K, typename V, typename Node>
class BaseTree
{
public:
    class Iterator;
    BaseTree()
        :_begin(nullptr),
         _end(nullptr)
    {
    }
    // BaseTree(const BaseTree &o)
    // {
    // }
    V &operator[](const K &key) const
    {
        return find(key)->second;
    }
    Iterator find(const K &key) const
    {
        return find(_root, key);
    }
public:
    class Iterator
    {
    public:
        Iterator (Node *node)
            :_node(node)
        {}
        Iterator &operator++(Iterator&)
        {
            _node = _node->next;
            return *this;
        }
        Iterator &operator--(Iterator&)
        {
            _node = _node->prev;
            return *this;
        }
        std::pair<K, V> &operator*()
        {
            return _node->data;
        }
        std::pair<K, V> &operator->()
        {
            return **this;
        }
    private:
        Node *_node;
    };
// protected:
public:
    Node *_root;
    Iterator _begin;
    Iterator _end;
private:
    Iterator find(Node *node, const K &key) const
    {
        if (!node) return _end;
        if (node->data->first == key) {
            return Iterator(node);
        }
        if (key < node->data->first) {
            return find(node->left, key);
        }
        return find(node->right, key);
    }
};
