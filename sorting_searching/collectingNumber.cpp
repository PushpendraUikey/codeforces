#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/2216

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    vector<int> arr(n+1);
    int val;
    for(int i=0; i<n; i++) {
        cin >> val;
        arr[val] = i;
    }
    
    int passes = 1;
    for (int i=1; i<n; i++) {
        if(arr[i+1] < arr[i]){  // Since position of `i+1` is lower than `i` I'm forced to make a pass
            passes++;       // I'm forced to make another pass.
        }
    }

    cout << passes << '\n';
}

/*
The "Collecting Numbers" problem (often from the CSES problem set) is a fantastic exercise in changing your perspective.

The naive way to think about it is to simulate the process: sweep through the array, pick up the numbers you need, and 
repeat until you have them all. The problem is that simulating worst-case scenarios (like the array `5 4 3 2 1`) will 
take $O(N^2)$ time, which will result in a Time Limit Exceeded (TLE) error.

To find the $O(N)$ solution, you have to invert how you think about the problem.

### The Shift in Perspective

Instead of asking, *"What numbers do I collect in Pass 1? What do I collect in Pass 2?"*

Ask yourself: **"When am I forced to start a new pass?"**

Imagine you are walking through the array from left to right, and you just picked up the number $X$. You are now looking 
for $X + 1$.

* **Case 1:** If $X + 1$ is physically located to the **right** of $X$ in the array, you can just keep walking forward 
and pick it up during the *same* pass.
* **Case 2:** If $X + 1$ is physically located to the **left** of $X$, you have a problem. You have already walked past 
it. You are forced to finish your current pass, go all the way back to the start, and begin a **new pass**.

### The $O(N)$ Logic

This insight means we actually don't care about the array values directly; we only care about their **positions**(indices).

1. Create a lookup array (or map) called `position` where `position[value]` gives you the index of that value in the 
    original array.
2. Start with `passes = 1` (since you always need at least one sweep).
3. Loop through the numbers you need to collect in order ($1, 2, 3 \dots N-1$).
4. If `position[X + 1] < position[X]`, it means the next number is behind you. Increment your `passes` counter.

### Walkthrough Example

Let's trace the array: `[4, 2, 1, 5, 3]`

First, build the `position` data (using 1-based indexing for simplicity):

* `pos[1] = 3`
* `pos[2] = 2`
* `pos[3] = 5`
* `pos[4] = 1`
* `pos[5] = 4`

Now, trace the jumps from $1 \dots 5$:

* **Find 1:** We are at index 3. Total passes = **1**.
* **Jump 1 to 2:** 2 is at index 2. We moved **left** (`pos[2] < pos[1]`). We need a **New Pass**. Total = **2**.
* **Jump 2 to 3:** 3 is at index 5. We moved right. Same pass. Total = 2.
* **Jump 3 to 4:** 4 is at index 1. We moved **left** (`pos[4] < pos[3]`). We need a **New Pass**. Total = **3**.
* **Jump 4 to 5:** 5 is at index 4. We moved right. Same pass. Total = 3.

**Result:** 3 passes.

*/