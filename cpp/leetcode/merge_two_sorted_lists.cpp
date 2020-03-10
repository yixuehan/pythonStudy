#include <iostream>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *n) : val(x), next(n) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode extra(0);
        ListNode *next = &extra;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                next->next = l1;
                l1 = l1->next;
            }
            else {
                next->next = l2;
                l2 = l2->next;
            }
            next = next->next;
        }
        next->next = l1 ? l1 : l2;
        return extra.next;
    }
};

ostream &operator<<(ostream &os, ListNode* l)
{
    for (auto next = l; next != nullptr; next = next->next) {
        os << next->val << ' ';
    }
    return os << endl;
}

int main()
{
    Solution s;
    ListNode l1{1, new ListNode{2, new ListNode{4, NULL}}};
    ListNode l2{1, new ListNode{3, new ListNode{4, NULL}}};
    cout << s.mergeTwoLists(&l1, &l2) << endl;
}
