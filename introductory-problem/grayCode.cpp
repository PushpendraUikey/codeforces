#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/2205

// i'th Gray code for an integer i can be calculated using the bitwise operation 
// G(i) = i ^ (i >> 1);
string convertToBinary(int n, int digit) {
    string ans = "";
    while(n) {
        int r = n%2;
        ans = r == 0 ? "0" + ans : "1" + ans;
        n >>= 1;
    }
    int len = digit - ans.length();
    for (int i=0; i<len; i++) ans = "0" + ans;
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;

    // don't want to use the configuration details as they are way too sort for this purpose?
    int last = pow(2,n);
    for(int i=0; i<last; i++) {
        int gray_value = i ^ (i>>1);
        cout << convertToBinary(gray_value, n) << '\n';
    }
}

/*
Here is an analysis of your Gray code algorithm, breaking down its logic, complexity, and areas for optimization.

### **1. Core Logic & Mechanics**

The algorithm relies on a highly efficient bitwise trick to generate Gray codes. A Gray code sequence is a binary 
numeral system where two successive values differ in only one bit.

* **The Mathematical Principle:** The $i$-th Gray code can be directly generated from the integer $i$ using the 
formula `G(i) = i ^ (i >> 1)`. This works because shifting the binary representation to the right by one and 
XORing it with the original number perfectly mirrors the standard Gray code construction (where the $k$-th bit 
of a Gray code is the XOR of the $k$-th and $(k+1)$-th bit of the standard binary number).
* **The Execution:**
1. The code calculates the total number of terms needed: $2^n$ (using `pow(2, n)`).
2. It iterates from $0$ to $2^n - 1$.
3. It applies the bitwise formula to get the integer value of the Gray code.
4. It converts that integer into an $n$-bit binary string and prints it.



### **2. Complexity Analysis**

* **Time Complexity: $\mathcal{O}(n^2 \cdot 2^n)$**
* The `main` loop runs $2^n$ times.
* Inside the loop, `i ^ (i >> 1)` evaluates in $\mathcal{O}(1)$ time.
* However, the `convertToBinary` function is the bottleneck. In C++, prepending to a string like `ans = "0" + ans` 
forces the program to allocate a new string and copy all existing characters. Doing this $n$ times results in 
$1 + 2 + 3 + \dots + n$ operations, making the string conversion $\mathcal{O}(n^2)$.
* Therefore, the total time complexity is strictly $\mathcal{O}(n^2 \cdot 2^n)$.


* **Space Complexity: $\mathcal{O}(n)$**
* The algorithm does not store the sequence in memory; it prints it on the fly. The only memory overhead is the 
string `ans` inside the `convertToBinary` function, which takes $\mathcal{O}(n)$ space.


### **3. Areas for Improvement (Code Review)**

While the mathematical logic is flawless, the C++ implementation has a few inefficiencies that could cause Time 
Limit Exceeded (TLE) errors on strict competitive programming platforms like CSES.

**A. Inefficient String Prepending**
As mentioned, `ans = "0" + ans` is slow. It is much faster to append to the end of a string and `reverse()` it, 
or—even better—manipulate a pre-sized string directly. Alternatively, since $n \le 16$ for this CSES problem, 
you can use `std::bitset`.

**B. Floating Point Math for Integers**
`pow(2, n)` returns a `double` and is relatively slow. In competitive programming, you should use bitwise shifts 
for powers of 2. `1 << n` is the integer equivalent of $2^n$ and evaluates in $\mathcal{O}(1)$ time.

**C. `while(n)` condition in binary conversion**
If $n=0$ is passed to `convertToBinary` (which happens on the very first iteration when $i=0$), the `while` loop 
is skipped entirely. Your padding logic handles it, but it does mean your function relies entirely on the padding 
loop for the `0` case.

### **4. Optimized Implementation**

Here is how you can optimize the algorithm to run in $\mathcal{O}(n \cdot 2^n)$ time by fixing the string generation 
and using bit shifts:

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // 1 << n is the fast, bitwise way to write 2^n
    int limit = 1 << n; 

    // Pre-allocate a string of '0's of length n
    string ans(n, '0'); 

    for (int i = 0; i < limit; i++) {
        int gray_value = i ^ (i >> 1);
        
        // Fast binary conversion by updating the pre-allocated string
        for (int j = 0; j < n; j++) {
            // Check the j-th bit of gray_value
            if ((gray_value >> j) & 1) {
                ans[n - 1 - j] = '1';
            } else {
                ans[n - 1 - j] = '0';
            }
        }
        cout << ans << '\n';
    }
    
    return 0;
}

```

**Why this is better:**

1. Avoids all string reallocation/copying ($\mathcal{O}(n)$ instead of $\mathcal{O}(n^2)$ per number).
2. Uses `1 << n` instead of `pow`, avoiding floating-point conversions.
3. Completely avoids string concatenation (`+`), interacting directly with character indices instead.
*/