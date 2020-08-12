#include "list.h"
#include <time.h>

int compare_int(const void *v1, const void *v2)
{
    int i1 = *(int*)v1;
    int i2 = *(int*)v2;
    if (i1 > i2) return -1;
    if (i1 == i2) return 0;
    return 1;
}

void show_int(const void *data)
{
    printf("%d ", *(const int*)data);
}

int main()
{
    CList list;
    init_list(&list, sizeof(int), NULL, show_int);
    // init_list(&list, sizeof(int), NULL, NULL);
    srand(time(NULL));
    for (int i = 0; i < 20; ++i) {
        int a = rand() % 1000;
        push_back(&list, &a);
    }
    printf("%p %p\n", list.head, list.tail);
    printf("------------------------------------------------\n");
    print_list(&list);
    printf("r----------------------------------------------r\n");
    print_list_r(&list);
    printf("------------------sort--------------------------\n");

    sort_list(&list, compare_int);
    printf("------------------------------------------------\n");
    print_list(&list);
    printf("r----------------------------------------------r\n");
    print_list_r(&list);

    int x = 119;
    pop_front(&list);
    pop_back(&list);
    push_front(&list, &x);
    printf("----------------change--------------------------\n");
    print_list(&list);
    CNode *node = list.head;
    for (int i = 0;i < 10; ++i) {
        node = node->next;
    }
    insert(&list, node, &x);
    remove_node(&list, node);
    printf("----------------change--------------------------\n");
    print_list(&list);

    clear(&list);
    printf("----------------clear---------------------------\n");
    print_list(&list);
}
