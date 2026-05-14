#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1630

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int a, d;
    vector<pair<int,int>> arr(n);
    for(int i=0; i<n; i++) {
        cin >> a >> d;
        arr[i] = {a, d};
    }

    sort(arr.begin(), arr.end());
    ll reward = 0;
    ll dur = 0;
    for(int i=0; i<n; i++) {
        dur += arr[i].first;
        reward += (arr[i].second - dur);
    }

    cout << reward << '\n';
}

/*
Gemini Review:
You are referring to the exact mathematical trick at the heart of the classic **Tasks and Deadlines** problem 
(often seen in competitive programming like the CSES problem set).

It feels counterintuitive to ignore deadlines when the problem explicitly gives them to you. However, the greedy 
approach works—specifically, sorting strictly by **Shortest Duration (Processing Time) First**—because of how 
the reward formula mathematically simplifies.

Here is the straightforward breakdown of why the deadlines become irrelevant to your sorting logic.

### 1. The Mathematical Invariant

Let's look at the formula for your total reward. For every task, your reward is calculated as its deadline minus its 
finish time: `Reward = d - f`.

If you have $N$ tasks, your total score is the sum of all individual rewards:


$$Total = (d_1 - f_1) + (d_2 - f_2) + \dots + (d_n - f_n)$$

By grouping the variables together using basic algebra, we can rewrite this as:


$$Total = (d_1 + d_2 + \dots + d_n) - (f_1 + f_2 + \dots + f_n)$$

$$Total = \sum d_i - \sum f_i$$

### 2. Why the Deadlines Drop Out

Look closely at $\sum d_i$ (the sum of all deadlines). Because the problem states that **all tasks must be processed**, 
the sum of their deadlines will always be the exact same number, no matter what order you process them in. It is a 
**constant**.

Let's call that constant $C$. The formula is now simply:


$$Total = C - \sum f_i$$

To make your total score as large as possible, you must subtract the smallest possible number from $C$. Therefore, 
the problem completely sheds the concept of deadlines and transforms into a single, simpler goal: **Minimize the 
sum of all finish times.**

### 3. Minimizing Finish Times (The Greedy Choice)

How do you minimize the sum of finish times? By processing the shortest tasks first. This is proven by an **exchange 
argument**.

Imagine you have Task A (takes 2 hours) and Task B (takes 10 hours).

* **Longest First (B then A):** Task B finishes at hour 10. Task A finishes at hour 12 (10 + 2).
* *Sum of finish times:* $10 + 12 = \mathbf{22}$


* **Shortest First (A then B):** Task A finishes at hour 2. Task B finishes at hour 12 (2 + 10).
* *Sum of finish times:* $2 + 12 = \mathbf{14}$



Notice that the total time taken to do both tasks is always exactly 12 hours. The final finish time never changes. 
However, by putting the short task first, you "lock in" a very small finish time early on, preventing that task from 
waiting around and accumulating a massive delay while the long task runs.

### Summary

You ignore the deadlines because they are an unchangeable constant in the final equation. You use the greedy approach 
(Shortest Duration First) because delaying a short task behind a long task strictly damages your sum of finish times, 
which directly lowers your total reward.

---

Here is an interactive visualizer that proves the exchange argument. You can see exactly how the order of tasks changes 
the *sum* of finish times, even though the total time to complete all tasks (the makespan) never changes.
*/