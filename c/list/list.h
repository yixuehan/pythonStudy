#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// 双向链表定义
typedef struct _node
{
    struct _node *next;
    struct _node *prev;
    void *data;
} CNode;

// 初始化结点
void init_node(CNode *node, int data_size)
{
    memset(node, 0, sizeof(CNode));
    node->data = malloc(data_size);
}

// 释放结点
void free_node(CNode *node)
{
    free(node->data);
    node->data = NULL;
    free(node);
}

typedef CNode *Iterator;

typedef void (*CopyFunc)(void *dst, const void *copy);
typedef int (*CompareFunc)(const void *dst, const void *copy);
typedef void (*ShowFunc)(const void *data);

typedef struct _list
{
    CNode *head;
    CNode *tail;
    int length;
    int data_size;
    CopyFunc copy_func;
    CompareFunc compare_func;
    ShowFunc show_func;
} CList;

// 默认的拷贝方式就是内存拷贝
void default_copy_func(void *dst, const void *src, size_t size)
{
    memcpy(dst, src, size);
}

// 初始化链表
void init_list(CList *list, int data_size,
        CopyFunc copy_func,
        ShowFunc show_func)
{
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->data_size = data_size;

    list->copy_func = copy_func;
    list->show_func = show_func;
}

// 创建新的结点
CNode *new_node(CList *list, void *data)
{
    CNode *node = (CNode*)malloc(sizeof(CNode));
    init_node(node, list->data_size);
    if (list->copy_func)
        list->copy_func(node->data, data);
    else
        default_copy_func(node->data, data, list->data_size);
    return node;
}

// 头部插入
void push_front(CList *list, void *data)
{
    CNode *next = list->head;
    list->head = new_node(list, data);
    list->head->next = next;
    if (NULL == list->tail) {
        list->tail = list->head;
    } else {
        next->prev = list->head;
    }
    ++(list->length);
}

// 尾部插入
void push_back(CList *list, void *data)
{
    CNode *prev = list->tail;
    list->tail = new_node(list, data);
    list->tail->prev = prev;
    if (NULL == list->head) {
        list->head = list->tail;
    } else {
        prev->next = list->tail;
    }
    ++(list->length);
}

// 指定位置插入
void insert(CList *list, Iterator iter, void *data)
{
    if (iter == list->head) {
        push_front(list, data);
        return;
    }
    if (iter == list->tail) {
        push_back(list, data);
        return;
    }
    CNode *node = new_node(list, data);
    node->prev = iter->prev;
    node->next = iter->next;
    iter->prev->next = node;
    iter->prev = node;
    ++(list->length);
}

// 头部删除
void pop_front(CList *list)
{
    if (NULL == list->head) {
        return;
    }
    CNode *node = list->head;
    list->head = list->head->next;
    if (NULL == list->head) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }
    free_node(node);
    --(list->length);
}

// 尾部删除
void pop_back(CList *list)
{
    if (NULL == list->tail) {
        return;
    }
    CNode *node = list->tail;
    list->tail= list->tail->prev;
    if (NULL == list->tail) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }
    free_node(node);
    --(list->length);
}

// 删除节点
void remove_node(CList *list, Iterator iter)
{
    if (iter == list->head) {
        pop_front(list);
        return;
    }
    if (iter == list->tail) {
        pop_back(list);
        return;
    }
    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
    free_node(iter);
    --(list->length);
}

// 删除链表
void clear(CList *list)
{
    CNode *node = list->head;
    while (node) {
        list->head = list->head->next;
        free_node(node);
        node = list->head;
    }
    list->tail = NULL;
    list->length = 0;
}

// 获取中间结点(内部方法)
CNode *get_mid_node(CNode *node)
{
    CNode *fast = node;
    while (true) {
        if (!fast) break;
        fast = fast->next;
        if (!fast) break;
        fast = fast->next;
        node = node->next;
    }
    return node;
}

// 合并链表(内部方法)
CNode *merge_list_node(CList *list, CNode *l1, CNode *l2)
{
    CNode head;
    CNode *node = &head;
    while (l1 && l2) {
        if (list->compare_func(l1->data, l2->data) < 0) {
            l1->prev = node;
            node->next = l1;
            l1 = l1->next;
            node = node->next;
        } else {
            l2->prev = node;
            node->next = l2;
            l2 = l2->next;
            node = node->next;
        }
    }
    CNode *left = l1 ? l1 : l2;
    while (left) {
        left->prev = node;
        node->next = left;
        node = node->next;
        left = left->next;
    }
    head.next->prev = NULL;
    return head.next;
}

// 递归排序
CNode *sort_list_node(CList *list, CNode *node)
{
    if (!node || !(node->next)) {
        return node;
    }
    CNode *head1 = node;
    CNode *head2 = get_mid_node(node);
    head2->prev->next = NULL;
    head2->prev = NULL;
    head1 = sort_list_node(list, head1);
    head2 = sort_list_node(list, head2);
    return merge_list_node(list, head1, head2);
}

// 归并排序
void sort_list(CList *list, CompareFunc compare_func)
{
    if (list->length < 2) return;
    if (!compare_func) {
        printf("no compare func");
        return;
    }
    list->compare_func = compare_func;

    list->head = sort_list_node(list, list->head);
    list->tail = list->head;
    int length = 0;
    if (list->tail) length = 1;
    while (list->tail && list->tail->next) {
        list->tail = list->tail->next;
        ++length;
    }
    assert (length == list->length);
}

// 正向遍历
void print_list(CList *list) {
    CNode *node = list->head;
    while (node) {
        if (list->show_func)
            list->show_func(node->data);
        node = node->next;
    }
    printf("\n");
}

// 反向遍历
void print_list_r(CList *list) {
    CNode *node = list->tail;
    while (node) {
        if (list->show_func)
            list->show_func(node->data);
        node = node->prev;
    }
    printf("\n");
}
