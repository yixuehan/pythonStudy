#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct _node
{
    struct _node *next;
    struct _node *prev;
    void *data;
} CNode;

void init_node(CNode *node, int data_size)
{
    memset(node, 0, sizeof(CNode));
    node->data = malloc(data_size);
}

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

void default_show_func(const void *data)
{
    printf("%d ", *(const int*)data);
}

void default_copy_func(void *dst, const void *src)
{
    memcpy(dst, src, sizeof(int));
}

int default_compare_func(const void *v1, const void *v2)
{
    int i1 = *(const int*)v1;
    int i2 = *(const int*)v2;
    if (i1 < i2) return -1;
    if (i1 == i2) return 0;
    return 1;
}

void init_list(CList *list, int data_size,
        CopyFunc copy_func,
        CompareFunc compare_func,
        ShowFunc show_func)
{
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->data_size = data_size;

    if (!copy_func)
        copy_func = default_copy_func;
    list->copy_func = copy_func;
    if (!show_func)
        show_func = default_show_func;
    list->show_func = show_func;
    if (!compare_func)
        compare_func = default_compare_func;
    list->compare_func = compare_func;
}

CNode *new_node(CList *list, void *data)
{
    CNode *node = (CNode*)malloc(sizeof(CNode));
    init_node(node, list->data_size);
    list->copy_func(node->data, data);
    return node;
}

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
void sort_list(CList *list)
{
    if (list->length < 2) return;
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

void print_list(CList *list) {
    CNode *node = list->head;
    while (node) {
        list->show_func(node->data);
        node = node->next;
    }
    printf("\n");
}

void print_list_r(CList *list) {
    CNode *node = list->tail;
    while (node) {
        list->show_func(node->data);
        node = node->prev;
    }
    printf("\n");
}
