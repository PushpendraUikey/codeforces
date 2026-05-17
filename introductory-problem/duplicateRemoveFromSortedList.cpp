#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return nullptr;
        int lastval = head->val;
        ListNode* curr = head->next;
        set<int> duplicates;
        while (curr) {
            if (curr->val == lastval) {
                duplicates.insert(lastval);
            } else {
                lastval = curr->val;
            }
            curr = curr->next;
        }

        ListNode* newhead = new ListNode();
        ListNode* currnew = newhead;
        ListNode* temp = nullptr;
        curr = head;

        while (curr) {
            if (duplicates.count(curr->val) > 0) {
                temp = curr->next;
                currnew->next = temp;
                curr->next = nullptr;
                delete curr;
                curr = temp;
            } else {
                currnew->next = curr;
                currnew = curr;
                curr = curr->next;
            }
        }
        currnew->next = nullptr;
        return newhead->next;
    }
};

/*
Your logic correctly identifies the core challenge: you need to completely remove any number that appears more than once. 
However, your current implementation has a couple of drawbacks:

1. **Space Complexity:** You are using a `std::set` to store duplicates. This requires **O(N)** extra memory. Since the problem 
assumes the input list is *already sorted*, all duplicates will be sitting right next to each other, meaning you can detect 
them without extra data structures.
2. **Two Passes:** You iterate through the list once to find duplicates, and a second time to remove them. This can be done in 
a single pass.
3. **Pointer Wiring Complexity:** Managing `currnew`, `curr`, and `temp` while deleting nodes makes the second loop quite 
fragile and prone to segmentation faults.

### The Optimal Approach: Single Pass with a Dummy Node

Since the list is already sorted, you can solve this in **O(N)** time and **O(1)** extra space by using two pointers 
(`prev` and `curr`) and a **Dummy Node**.

The dummy node sits right before the `head`. This is a crucial trick because if the very first elements in the list 
are duplicates (e.g., `1 -> 1 -> 2`), the actual `head` needs to change. The dummy node anchors the list so you always 
have a safe starting point.

Here is the clean, optimized C++ solution:

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // Dummy node acts as a safe anchor before the head
        ListNode* dummy = new ListNode(0, head);
        
        // 'prev' points to the last node that is guaranteed to be unique
        ListNode* prev = dummy;
        // 'curr' is used to scan the list
        ListNode* curr = head;
        
        while (curr != nullptr) {
            // Check if we've hit a sequence of duplicates
            if (curr->next != nullptr && curr->val == curr->next->val) {
                // Fast-forward 'curr' to the very last duplicate in this sequence
                while (curr->next != nullptr && curr->val == curr->next->val) {
                    curr = curr->next;
                }
                // Skip the entire duplicate sequence by linking 'prev' past 'curr'
                prev->next = curr->next; 
            } else {
                // If it's a unique value, simply move 'prev' forward
                prev = prev->next;
            }
            // Always move 'curr' to the next node to continue scanning
            curr = curr->next;
        }
        
        // Store the actual new head
        ListNode* newHead = dummy->next;
        delete dummy; // Clean up the dummy node to prevent memory leaks
        
        return newHead;
    }
};

```
*/