#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://www.geeksforgeeks.org/batch/dsa-4/track/DSASP-Graph/problem/minimum-swaps
// Following algorithm works for distinct ele in the arrayy only. 
// For duplicate ele, we can use pair of (ele, index) to sort and create adj list.
class Solution {
  public:
    // Function to find the minimum number of swaps required to sort the array.
    int minSwaps(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int,int> indx;
        unordered_map<int,int> adj;
        vector<bool> visited(n, false);
        int minSwap = 0;

        for(int i=0; i<n; i++) {
            indx[arr[i]] = i;
        }
    
        sort(arr.begin(), arr.end());

        for (int i=0; i<n; i++) {
            adj[i] = indx[arr[i]];
        }
        
        for (int i=0; i<n; i++) {
            if(!visited[i]) {
                queue<int> q;
                q.push(i);
                visited[i] = true;
                int cnt = 0;
                while(!q.empty()) {
                    int u = q.front();  q.pop();
                    cnt++;
                    int v = adj[u];
                    if(!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
                minSwap += (cnt-1); // for cycle of size n, we need n-1 swaps to arrange it.
            }
        }
        
        return minSwap;
    }
};

/*
The relationship between **disjoint cycles** and the **minimum swaps to sort an array** is a beautiful application 
of graph theory.

To understand why they are connected, we can look at a classic analogy.

### The Analogy: The "Secret Santa" Gift Mix-Up

Imagine you are at an office party where 5 people brought Secret Santa gifts. Instead of handing them out correctly, 
the organizer randomly placed one gift on each person's desk.

You are tasked with fixing this, but you can only carry one gift at a time, swapping it with whatever is currently 
on a desk.

Here is how you do it:

1. You go to Alice's desk and pick up the gift sitting there. It belongs to Charlie.
2. You walk over to Charlie's desk, give him his gift, and pick up the incorrect gift sitting on his desk. 
   It belongs to Dave.
3. You go to Dave's desk, give him his gift, and pick up the gift there. It belongs to Alice!
4. You return to Alice, hand her the final gift, and you're done.

Notice what just happened? You traveled in a closed loop: **Alice → Charlie → Dave → Alice**.
Once you returned to Alice, everyone in that loop had their correct gift.

Because nobody in this loop has a gift belonging to someone outside the loop, this is a **Disjoint Cycle**. 
If there are other people with mixed-up gifts (say, Bob and Eve swapped with each other), they form their 
*own* completely separate cycle (**Bob → Eve → Bob**).

### The Mathematical Translation

An array is just a line of "desks" (indices) holding "gifts" (values).

When you want to find the minimum number of swaps to sort an array, you are essentially asking: *How many times 
do I have to exchange items to resolve all the mix-ups?*

If you map out where every element currently is versus where it *should* be, the array naturally breaks down into 
these independent, disjoint cycles.

**The Golden Rules of Cycles:**

1. **A cycle of length 1** means the element is already in the correct spot. It requires **0 swaps**.
2. **A cycle of length 2** (like Bob and Eve) requires exactly **1 swap** to fix both elements.
3. **A cycle of length *k*** requires exactly ***k - 1* swaps** to resolve. (In our 3-person cycle with Alice, 
       Charlie, and Dave, it took 2 swaps).

Because the cycles are entirely disjoint (they don't overlap), you can just add up the swaps needed for each 
individual cycle to get the absolute minimum number of swaps for the whole array.

**The Formula:**
If an array has `N` total elements, and you decompose it into `C` disjoint cycles, the minimum number of swaps 
    required to sort the array is exactly:
**Minimum Swaps = N - C**

*/

/*
// Gemini written Code:

Your logic is algorithmically sound, and you correctly applied the graph theory concept of disjoint cycles! The 
formula `minSwap += (cnt - 1)` is exactly right.

However, from a C++ performance and design standpoint, this code is significantly over-engineered and will run 
much slower than it needs to.

Here is a breakdown of what you did well, the hidden bottlenecks in your approach, and how to write the "industry 
standard" optimized version.

### 👍 What You Did Right

1. **The Math is Perfect:** You correctly identified that minimum swaps equal the sum of `(cycle_size - 1)` for all 
    disjoint cycles.
2. **Cycle Detection:** You correctly avoided infinite loops by using a `visited` array.

### 🚩 The Bottlenecks

**1. The `unordered_map` Trap**
Using two `unordered_map`s is the biggest performance killer here. Hash maps have a massive constant time overhead. 
Because the array elements and indices are just linear data, you don't need to hash them.

**2. BFS with a `queue` is Overkill**
You used a Breadth-First Search queue to traverse the cycle. But remember: in a permutation graph, every node has 
exactly one outgoing edge and one incoming edge. It's a single, closed loop. You don't need a queue to explore 
branches because there are no branches! You can just use a simple `while` loop to jump from one node to the next.

**3. Modifying the Input Array**
You did `sort(arr.begin(), arr.end());` directly on the input array. In a real-world software system (or an interview),
 mutating the input array when the function signature doesn't imply it is generally frowned upon, as it destroys 
 the data the caller passed to you.

---

### 🛠️ The Standard Optimized Approach: `vector<pair<int, int>>`

You actually mentioned the fix in your own comments: *"For duplicate ele, we can use pair of (ele, index)"*.
You should use this exact technique even for distinct elements! It completely eliminates the need for hash maps 
and handles duplicates automatically.

Here is the highly optimized, clean version:

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& arr) {
        int n = arr.size();
        
        // Step 1: Create a vector of pairs {element_value, original_index}
        vector<pair<int, int>> vec(n);
        for (int i = 0; i < n; i++) {
            vec[i] = {arr[i], i};
        }
        
        // Step 2: Sort the vector based on values
        sort(vec.begin(), vec.end());
        
        vector<bool> visited(n, false);
        int minSwap = 0;
        
        // Step 3: Find cycles
        for (int i = 0; i < n; i++) {
            // If already visited, or already in the correct position, skip
            if (visited[i] || vec[i].second == i) {
                continue;
            }
            
            // Traverse the cycle
            int cycle_size = 0;
            int j = i;
            
            while (!visited[j]) {
                visited[j] = true;
                j = vec[j].second; // Jump to where this element originally came from
                cycle_size++;
            }
            
            // Add (cycle_size - 1) to total swaps
            if (cycle_size > 0) {
                minSwap += (cycle_size - 1);
            }
        }
        
        return minSwap;
    }
};

### 🔍 Why this is much better:

***No Hash Maps:** The `pair` keeps the original index tied to the value permanently. Sorting the pairs takes 
$O(N \log N)$ time, and there is $0$ hashing overhead.
***No Queues:** The `while (!visited[j])` loop acts as an $O(1)$ memory DFS. It just follows the pointer 
`j = vec[j].second` until it hits an already visited node.
***Non-Destructive:** The original `arr` is never modified.
***Duplicate Safe:** Because `std::sort` on pairs sorts by the first element (the value) and then by the second 
element (the original index), it naturally and safely groups duplicate elements together without breaking the logic.
*/