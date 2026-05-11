#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/group/KQjBMkHxUY/contest/621334/problem/A

void solve(int a, int b) {
    if(b > a) return solve(b, a);
    int v = min((a-b)/2, b);
    a -= 3*v;
    b -= v;
    if(b==0) {
        cout << v << '\n';
        return;
    }
    int ans = min(b/2, a/2) + v;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    if(!(cin>>tt)) return 0;
    while(tt--) {
        int a, b;
        if(!(cin>>a>>b)) continue;;
        solve(a, b);
    }
}

/*
Gemini Response:
Here is an analysis of your algorithm, breaking down its mathematical foundation, its edge cases, and a massive 
simplification you can use.

### **1. What This Algorithm Solves**

Although you didn't provide the problem description, your logic perfectly perfectly matches a specific variation 
of resource allocation: **Forming the maximum number of groups of 4**.

Specifically, it calculates the maximum number of operations you can perform if your allowed operations are:

* Consume 3 from $A$ and 1 from $B$ (Cost: 4)
* Consume 2 from $A$ and 2 from $B$ (Cost: 4)
* Consume 1 from $A$ and 3 from $B$ (Cost: 4)

This translates to forming teams of 4 people where every team must have at least one person from pool $A$ and at 
least one from pool $B$.

### **2. Core Logic & Mechanics**

Your constructive approach is highly logical and mathematically sound. You are using a greedy strategy to balance 
the two pools:

1. **Ensure $A \ge B$:** Your swap `if(b > a)` ensures you always process the larger pool first.
2. **Greedy Balancing:** You calculate `v = min((a-b)/2, b)`. Because picking a (3, 1) team reduces the difference 
    between the pools by exactly 2, dividing the difference by 2 gives you the ideal number of (3, 1) teams needed 
    to make $a$ and $b$ as equal as possible. You cap this at `b`, because you can't form a team without at least 
    one element from $B$.
3. **Subtract Resources:** `a -= 3*v` and `b -= v` safely removes those formed teams from the available pool.
4. **Pairing the Rest:** Once the pools are balanced, you switch to forming (2, 2) teams with `min(b/2, a/2)`.
5. **Total:** The answer is the sum of the (3, 1) teams and the (2, 2) teams.

### **3. Complexity & Redundancy**

* **Time Complexity: O(1)**. You are using pure math, avoiding any loops. This is optimal and will effortlessly pass 
    $10^5$ test cases.
* **Space Complexity: O(1)**.
* **Redundancy Check:** Your early exit `if(b==0)` is technically redundant. If $b = 0$, the math evaluates to 
`min(0/2, a/2) + v`, which naturally becomes `0 + v = v`. The code will execute perfectly without that block.

### **4. The $O(1)$ "One-Liner" Optimization**

Your greedy logic effectively reverse-engineers a mathematical truth about this specific constraint. Because every 
valid team consumes exactly 4 total resources, and requires at least 1 from each pool, the maximum number of teams 
is strictly bound by three bottlenecks:

1. You can't have more teams than total items in pool $A$.
2. You can't have more teams than total items in pool $B$.
3. You can't have more teams than $\lfloor(A + B) / 4\rfloor$.

Because your algorithm perfectly respects these bottlenecks, your entire `solve` function can be replaced by a 
single, mathematically equivalent line:

```cpp
void solve(int a, int b) {
    // The maximum teams of 4 is the minimum of the three possible bottlenecks.
    cout << min({a, b, (a + b) / 4}) << '\n';
}

```

### **Interactive Visualization**

To see exactly how your constructive logic (the "Greedy Steps") mirrors the one-line formula across different 
scenarios, here is an interactive calculator. You can adjust the pools to see how your algorithm breaks down the 
operations versus how the formula calculates the ceiling.
*/