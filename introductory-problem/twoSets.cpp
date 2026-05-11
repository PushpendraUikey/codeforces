#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1092
/*
Your task is to divide the numbers 1,2,\ldots,n into two sets of equal sum.
Input: The only input line contains an integer n.
Output: Print "YES", if the division is possible, and "NO" otherwise.
After this, if the division is possible, print an example of how to create the sets. First, print the number 
of elements in the first set followed by the elements themselves in a separate line, and then, print the 
second set in a similar way. 

Constraints: 1 <= n <= 10^6
*/

int main() {
    ll n;
    cin >> n;
    ll tn = n;
    ll t = n+1;
    if(tn%2==0) {
        tn /= 2;
    } else{
        t  /= 2;
    }
    ll total = t*tn;
    if(total % 2 == 1) {
        cout << "NO\n";
    } else {
        total /= 2;
        vector<bool> first(n+1, false);
        int cnt = 0;
        int j = n;
        while(j>0 && total > 0) {
            total -= j;
            cnt++;
            first[j] = true;
            if(total==0) {
                break;
            }
            j--;
            while(total < j && j > 0) {
                j = (j+1)/2;
            }
        }
        if(total != 0) {
            for(int i=1; i<=n; i++) {
                if(!first[i] && i == total) {
                    first[i] = true;
                    cnt++;
                    break;
                }
            }
        }
        cout << "YES\n";
        cout << cnt << '\n';
        for(int i=1; i<=n; i++){
            if(first[i]){
                cout << i << ' ';
            }
        }
        cout << '\n';
        cout << n-cnt << '\n';
        for(int i=1; i<=n; i++) {
            if(!first[i]){
                cout << i << ' ';
            }
        }
        cout << '\n';
    }
}

/*
// Gemini's insight:
Here is an analysis of your algorithm, breaking down what works well, the underlying time/space complexity, and areas 
where the logic can be significantly simplified.

### 1. Overall Verdict

Your code correctly solves the CSES "Two Sets" problem. It efficiently handles the math to prevent integer overflow 
and correctly implements a greedy approach to partition the sets. It will easily pass the constraints ($n \le 10^6$) 
well within the time limit.

### 2. Time and Space Complexity

* **Time Complexity:** $\mathcal{O}(N)$. The math operations at the beginning take $\mathcal{O}(1)$ time. The `while` 
loops for the greedy choice run in at most $\mathcal{O}(N)$ steps. The final loops to print the elements run exactly 
in $\mathcal{O}(N)$ time.
* **Space Complexity:** $\mathcal{O}(N)$. You are allocating a `vector<bool>` of size $N+1$ to keep track of the 
elements in the first set, which is optimal for this problem.

### 3. Core Logic Breakdown & Strong Points

* **Preventing Overflow:** Calculating the sum of an arithmetic progression as $\frac{n(n+1)}{2}$ can easily overflow 
a 32-bit integer when $n = 10^6$. Your strategy of dividing by `2` *before* multiplying (`if(tn%2==0) { tn /= 2; } 
else { t /= 2; }`) is a very safe, defensive programming habit.
* **The Parity Check:** You correctly identified that if the total sum is odd (`total % 2 == 1`), it is impossible 
to divide it into two equal integer halves, correctly outputting `"NO"`.

### 4. Insights and Areas for Improvement

While your code works, the logic used to pick the numbers for the first set is unnecessarily convoluted.

**The Strange `j = (j+1)/2` Loop:**

```cpp
while(total < j && j > 0) {
    j = (j+1)/2;
}

```

You are using this to rapidly shrink `j` when the remaining `total` is smaller than the current number. However, 
this is not needed. Because you are processing numbers in strictly descending order (starting from $n$), if 
`total < j`, **you are guaranteed that the number exactly equal to `total` has not been used yet.**

Instead of jumping `j` down geometrically, you could simply grab the exact number you need (`total`), mark it 
as used, and terminate.

**The Redundant $\mathcal{O}(N)$ Search:**

```cpp
if(total != 0) {
    for(int i=1; i<=n; i++) {
        if(!first[i] && i == total) { ... }
    }
}

```

Because of the loop mentioned above, your algorithm sometimes breaks before `total` reaches `0`. You then use a 
`for` loop from $1$ to $n$ to find the exact number equal to `total`.
Since you already know the index you need is `total`, iterating through the entire array is unnecessary. 
You could just write: `first[total] = true; cnt++;`.

### 5. The Simplified Approach (Standard Greedy)

The logic of finding a subset that sums to exactly half of the total can be written much more cleanly. If you 
iterate downwards from $n$ to $1$, you can just take the current number if it fits into your remaining target sum.

Here is how you can refactor your code to be highly readable, eliminating the manual index jumping and the boolean 
array entirely:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    
    // Total sum formula: n*(n+1)/2
    ll total_sum = n * (n + 1) / 2;

    // If the total sum is odd, we can't split it evenly
    if (total_sum % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    ll target = total_sum / 2;
    vector<int> set1, set2;

    // Greedy approach: Go from largest to smallest
    for (int i = n; i >= 1; i--) {
        if (target >= i) {
            set1.push_back(i);
            target -= i;
        } else {
            set2.push_back(i);
        }
    }

    // Print Set 1
    cout << set1.size() << '\n';
    for (int x : set1) {
        cout << x << ' ';
    }
    cout << '\n';

    // Print Set 2
    cout << set2.size() << '\n';
    for (int x : set2) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}

```
### Why this refactor is better:
1. **Readability:** The greedy logic is condensed into a simple 7-line `for` loop. It asks a simple question: 
*"Can I fit the current number `i` into my remaining target? If yes, take it. If no, put it in the other set."*
2. **No Boolean Arrays:** By using two separate vectors, you avoid having to iterate through a boolean array twice 
just to print the elements out.
3. **Fast I/O:** Added `ios_base::sync_with_stdio(false); cin.tie(NULL);` which is a standard competitive 
programming practice to ensure your `cin`/`cout` operations don't cause Time Limit Exceeded (TLE) errors on 
large inputs.
*/