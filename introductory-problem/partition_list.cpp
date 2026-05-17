#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* curr = head;
        ListNode* temp = nullptr;
        ListNode* lastUnchanged = nullptr;
        ListNode* last = new ListNode();
        ListNode* superhead = last;
        ListNode* prev = new ListNode();

        while(curr) {
            if(curr->val < x) {
                temp = curr->next;
                last->next = curr;
                last = curr;
                last->next = lastUnchanged;
                curr = temp;
                prev->next = temp;
            } else{
                if(!lastUnchanged) lastUnchanged = curr;
                prev = curr;
                curr = curr->next;
            }
        }
        last->next = lastUnchanged;
        return superhead->next ? superhead->next : lastUnchanged;
    }
};

/*
Your current approach tries to modify the list in place by carefully rewiring pointers (`prev`, `lastUnchanged`, `last`, etc.) 
around a moving `curr` node. While an in-place approach is possible, it gets incredibly tricky. You have to handle edge cases 
(like when the head itself needs to move) and are highly prone to creating infinite cycles. For instance, the line 
`last->next = lastUnchanged;` inside your loop can easily link a node backwards to an earlier part of the list, 
creating a cycle.

### The Standard (and Much Easier) Solution: The Two-List Approach

The cleanest and most robust way to solve this problem is to create **two separate lists** using dummy nodes, and then merge 
them at the end.

1. **`lessHead`**: A dummy node to start a list for all values `< x`.
2. **`greaterHead`**: A dummy node to start a list for all values `>= x`.

**How it works:**

* You iterate through the original list once.
* If a node's value is less than `x`, you append it to the `less` list.
* If it's greater than or equal to `x`, you append it to the `greater` list.
* At the very end, you connect the tail of the `less` list to the actual first node of the `greater` list.

Here is the corrected and optimized code:

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        // Dummy nodes to anchor our two new lists
        ListNode* lessHead = new ListNode(0);
        ListNode* greaterHead = new ListNode(0);
        
        // Tails of the two lists, used to append new nodes
        ListNode* less = lessHead;
        ListNode* greater = greaterHead;
        
        ListNode* curr = head;
        
        // Traverse the original list and distribute nodes
        while (curr != nullptr) {
            if (curr->val < x) {
                less->next = curr;
                less = less->next;
            } else {
                greater->next = curr;
                greater = greater->next;
            }
            curr = curr->next;
        }
        
        // CRITICAL: Terminate the 'greater' list to prevent infinite cycles.
        // Without this, the last node might still point to a node in the 'less' list.
        greater->next = nullptr;
        
        // Connect the end of the 'less' list to the start of the 'greater' list
        less->next = greaterHead->next;
        
        // Store the actual head of the newly combined list
        ListNode* newHead = lessHead->next;
        
        // Clean up the dynamically allocated dummy nodes to prevent memory leaks
        delete lessHead;
        delete greaterHead;
        
        return newHead;
    }
};

```

### Why this approach is better:

* **No Cycles:** By explicitly setting `greater->next = nullptr` at the end, you guarantee your final list is properly terminated.
* **Easy Edge Cases:** Dummy nodes automatically handle the annoying edge cases, such as when the original list is empty, 
    or when all nodes end up in just one of the two partitions.
* **Complexity:** It runs in **O(N)** time because we only traverse the list once. It runs in **O(1)** auxiliary space because 
    we are only rearranging existing nodes, not creating new ones (aside from the two temporary dummy nodes).
*/