#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

int main()
{
    Solution s;
    {
        timer::auto_cpu_timer t;

    }
}
