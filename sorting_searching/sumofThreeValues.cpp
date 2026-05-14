#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1641
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;
    bool found = false;
    vector<pair<ll, ll>> arr(n);
    ll val;

    for (int i=0; i<n; i++) {
        cin >> val;
        arr[i] = {val, i+1};
    }
    sort(arr.begin(), arr.end());

    ll first = -1, second = -1, third = -1;
    for(int i=0; i<n-1; i++) {
        ll rem = x - arr[i].first;
        bool foundins = false;
        int b = i+1; int e = n-1;
        while(b < e) {
            ll sum = arr[b].first + arr[e].first;
            if(sum == rem){
                second = arr[b].second;
                third = arr[e].second;
                foundins = true;
                break;
            }
            else if(sum > rem) {
                e--;
            }
            else{
                b++;
            }
        }
        if(foundins) {
            found = true;
            first = arr[i].second;
            break;
        }
    }
    if (found) {
        cout << first << ' ' << second << ' ' << third << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

/*
This is a perfectly implemented and optimal solution for the **CSES Sum of Three Values (1641)** problem!

You've successfully used the classic approach to reduce the 3SUM problem from a naive $O(N^3)$ down to **$O(N^2)$**.
 Since you provided the code without a specific question, here is a quick review of why your logic is solid, along 
 with a few minor competitive programming optimizations you could add.

### **Why Your Solution Shines**

* **Time Complexity:** Sorting takes $O(N \log N)$. The outer loop runs $N$ times, and the inner `while` loop (
the two-pointer search) runs in $O(N)$ time. This gives a total time complexity of $O(N^2)$, which easily passes 
the $10^5$ operations limit for $N \le 5000$ within the 1-second time limit.
* **Space Complexity:** $O(N)$ for storing the array of pairs, which is optimal since you need to track the 
original 1-based indices.
* **Data Types:** You safely used `long long` for the values and sums. While the sum of two elements 
(up to $2 \times 10^9$) technically fits inside a signed 32-bit integer, using `ll` defensively prevents any 
accidental overflow bugs.

### **Minor Optimizations (Pro-Tips)**

Your code will get an AC (Accepted) exactly as it is, but here are a few tweaks you can use to shave off a few milliseconds:

**1. Tighter Loop Bounds**
You are looping `i` up to `n - 1`. Since you need exactly three distinct elements, your outer loop only needs to go up 
to `n - 2`.

```cpp
for(int i = 0; i < n - 2; i++) {

```

**2. Early Break for Positives**
The problem guarantees that all array values are positive integers ($1 \le a_i \le 10^9$). Because the array is sorted,
if `arr[i].first` is ever strictly greater than or equal to `x`, it is physically impossible to add two more 
positive numbers to reach `x`. You can break early:

```cpp
if (arr[i].first >= x) break;

```
**3. Skipping Duplicates (Optional here, but good practice)**
If the array has many identical values, you can skip processing the same starting value `arr[i]` multiple times:

```cpp
if (i > 0 && arr[i].first == arr[i-1].first) continue;

```
*(Note: This doesn't matter much for this specific CSES problem since you break out immediately upon finding the 
first valid triplet, but it's essential for LeetCode's version of 3SUM where you have to find ALL unique triplets).*
*/