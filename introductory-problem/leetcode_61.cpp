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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || head->next == nullptr || k == 0) return head;
        ListNode* last = nullptr;
        ListNode* curr = head;
        int cnt = 0;
        while(curr) {
            cnt++;
            last = curr;
            curr = curr->next;
        }
        k = k%cnt;
        int rem = cnt - k;
        if(rem==0 || k==0) return head;

        curr = head;
        while(rem>1){
            curr = curr->next;
            rem--;
        }

        ListNode* newhead = curr->next;
        curr->next = nullptr;
        last->next = head;
        return newhead;
    }
};

/*
### What You Did Right

1. **Thorough Edge Case Handling:** Your initial check (`if(!head || head->next == nullptr || k == 0)`) perfectly catches empty 
    lists, single-node lists, and scenarios where rotation isn't requested, preventing unnecessary computations or segmentation faults.
2. **Smart Modulo Math:** You correctly recognized that rotating a list of length $N$ by $N$ steps results in the exact same 
    list. Doing `k = k % cnt` ensures your code runs efficiently even if $k$ is $2,000,000,000$.
3. **Clean Two-Step Traversal:** Your logic of finding the length/tail first, calculating the breakpoint (`cnt - k`), and then 
    traversing to that specific breakpoint is exactly how this problem is meant to be solved.
4. **No Memory Leaks:** You are rearranging existing nodes rather than creating new ones (aside from standard pointer variables),
    meaning your space complexity is firmly **O(1)**.

### A Minor Polish: The "Stop at Tail" Trick

In your first `while` loop, you iterate until `curr` falls off the end of the list (becomes `nullptr`), keeping track of the 
`last` node right before it falls off.

A slightly more idiomatic way to do this in C++ is to initialize your count at `1` and stop the loop when `curr->next` is 
`nullptr`. This guarantees `curr` stops *exactly* on the tail node, saving you from needing a separate `last` variable entirely.

Here is what that looks like integrated into your code:

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // Start count at 1, and 'curr' at head
        ListNode* curr = head;
        int cnt = 1; 

        // Stop WHEN we reach the tail, not after we fall off it
        while (curr->next != nullptr) {
            cnt++;
            curr = curr->next;
        }
        // At this point, 'curr' IS the tail node. No need for a 'last' variable!

        k = k % cnt;
        if (k == 0) return head;

        // Connect the tail to the head to form a temporary circle
        curr->next = head; 

        // Calculate steps to the new tail
        int rem = cnt - k;
        
        // Traverse to the new tail (starting from head again)
        curr = head; // Reuse 'curr' to find the break point
        while (rem > 1) {
            curr = curr->next;
            rem--;
        }

        // 'curr' is now the new tail. 'curr->next' is the new head.
        ListNode* newhead = curr->next;
        
        // Break the circle
        curr->next = nullptr;
        
        return newhead;
    }
};

```

### Why this structure is slightly cleaner:

By forming the circle *before* you find the breaking point (`curr->next = head;`), the mental model changes from "stitching two 
disconnected lists together" to simply "forming a ring and then cutting it at a specific link." It achieves the exact same 
result but often feels a bit more robust to write out during interviews.

*/