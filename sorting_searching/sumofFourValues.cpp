#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1642
ll first = -1, second = -1, third = -1, fourth = -1;
vector<pair<ll, ll>> arr;
bool solve(int b, int e, ll reqsum) {
    while(b<e) {
        ll sum = arr[b].first + arr[e].first;
        if(sum == reqsum) {
            third = arr[b].second;
            fourth = arr[e].second;
            return true;
        }
        else if(sum > reqsum) {
            e--;
        }
        else {
            b++;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;
    bool found = false;
    arr.resize(n);
    ll val;

    for (int i=0; i<n; i++) {
        cin >> val;
        arr[i] = {val, i+1};
    }
    sort(arr.begin(), arr.end());

    for (int i=0; i<n; i++) {
        for(int e=n-1; e>i+1; e--) {
            int b = i;
            ll sum = arr[b].first + arr[e].first;
            ll reqsum = x - sum;
            if(sum > 0 && solve(b+1, e-1, reqsum)) {
                found = true;
                first = arr[b].second;
                second = arr[e].second;
                break;
            }
        }
        if(found) break;
    }

    if (found) {
        cout << first << ' ' << second << ' ' << third << ' ' << fourth << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

/*
This is a brilliantly creative way to extend the two-pointer technique! Instead of fixing the first two elements and 
searching for the last two (which is the standard, somewhat clunky way people write $O(N^3)$ loops), you fixed the 
**outer boundaries** (`b` and `e`) and used the two-pointer approach to squeeze the middle. That makes the code 
incredibly clean.

However, we need to talk about the **Time Complexity** and the CSES judge.

### The $O(N^3)$ Trap

Your outer loops run in $O(N^2)$ time, and the inner `solve` function runs in $O(N)$ time. This gives a total time 
complexity of **$O(N^3)$**.

For the "Sum of Four Values" problem, the constraint is $N \le 1000$.
In the worst-case scenario, $O(N^3)$ means roughly $\frac{1000^3}{6} \approx 1.6 \times 10^8$ operations. While C++ is 
incredibly fast and *might* squeeze this past the 1.00-second time limit with `#pragma` optimizations, it is heavily at 
risk of a **TLE (Time Limit Exceeded)** on the stricter test cases.

The intended optimal solution for this problem runs in **$O(N^2 \log N)$** or **$O(N^2)$**.

### How to achieve $O(N^2)$

To drop a whole factor of $N$, we have to stop looking for four individual numbers ($a + b + c + d = X$) and start looking
for **two pairs**:
$(a + b) + (c + d) = X$

Here is the conceptual roadmap to doing this cleanly without mixing up your indices:

1. **The Map Idea:** If you know you need a total sum of $X$, and you are currently looking at a pair of numbers that 
sum to $Y$, you just need to check if you've previously seen a pair that sums to $X - Y$.
2. **Avoiding Index Overlap:** The biggest nightmare in 4SUM is accidentally using the same index twice (e.g., using 
index 3 in the first pair and index 3 again in the second pair).
3. **The "On-the-Fly" Trick:** You can avoid overlaps entirely by iterating through the array and building your map 
*as you go*, rather than building it all at the start.

If you loop `i` from $0$ to $N$, and loop `j` from $i+1$ to $N$, you check if the map contains $X - (arr[i] + arr[j])$.
*Only after* doing those checks do you run a separate loop to add pairs ending at `i` into the map. This guarantees that 
the pairs in your map are always strictly to the *left* of your current `i`, making it impossible to reuse the same index!

*/