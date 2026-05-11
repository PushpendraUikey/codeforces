#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1755

int main() {
    string s;
    if(!(cin>>s)) return 0;
    int n = s.length();
    vector<int> count(26, 0);
    for(int i=0; i<n; i++) {
        count[(s[i]-'A')]++;
    }

    bool found = false;
    int indx = -1;
    for(int i=0; i<26; i++) {
        if(count[i]%2 != 0) {
            if(found) {
                cout << "NO SOLUTION\n";
                return 0;
            }
            found = true;
            indx = i;
        }
    }

    int i = 0;
    for (int j=0; j<26; j++) {
        int v = count[j];
        if( v%2 == 0 ) {
            v /= 2;
            while(v-->0) {
                s[i] = (j+'A');
                s[n-1-i] = (j+'A');
                i++;
            }
        }
    }
    if(found) {
        int v = count[indx];
        while(v > 1){
            s[i] = (indx+'A');
            s[n-1-i] = (indx+'A');
            i++;
            v-=2;
        }
        s[i] = (indx+'A');
    }
    cout << s << '\n';
}

/*
Gemini's Review: 
Here is an analysis of your solution for the **Palindrome Reorder** problem.

### **1. Core Logic & Mechanics**

Your algorithm correctly identifies the fundamental mathematical properties of a palindrome:

* **The Rule of Symmetry:** In a palindrome, characters must mirror each other across the center. This means almost 
    every character must appear an even number of times to be split equally between the left and right halves.
* **The Single Odd Exception:** A palindrome can have at most *one* character with an odd frequency, which will sit 
    perfectly in the exact center of the string.
* **The Execution:**
1. You count the frequencies of all 26 uppercase letters.
2. You verify that there is no more than one character with an odd frequency. If there is, it's impossible, and you 
    abort with "NO SOLUTION".
3. You use two pointers (`i` and `n-1-i`) to modify the string **in-place**, dealing out the even-counted characters 
    symmetrically to the front and back.
4. You handle the odd-counted character (if it exists) at the very end, placing its pairs and then dropping the final 
    character in the dead center.



### **2. Complexity Analysis**

* **Time Complexity: $\mathcal{O}(N)$**
* You iterate through the string once to count characters ($\mathcal{O}(N)$).
* You iterate through the constant-sized alphabet array a couple of times ($\mathcal{O}(1)$).
* You iterate through the string a final time to place the characters ($\mathcal{O}(N)$).
* Overall time is strictly linear, which is optimal.


* **Space Complexity: $\mathcal{O}(1)$ Auxiliary Space**
* You use a `vector<int>` of fixed size 26, which takes constant space regardless of the string's length.
* By modifying the input string `s` directly, you cleverly avoid allocating a second string to build the answer. 
    This is highly efficient.



### **3. Areas for Improvement (Code Review)**

Your solution is fast and will easily pass the time limits. However, the code can be made much cleaner and less 
    prone to off-by-one errors.

**A. Overcomplicated Reconstruction Logic**
Your logic for placing the characters relies on manual pointer math (`n-1-i`) and splitting the logic between the 
    even characters and the odd character. It works, but it takes quite a few lines and nested loops.

**B. Missing Fast I/O**
Unlike your previous code, you forgot to include `ios_base::sync_with_stdio(false); cin.tie(nullptr);`. While string 
operations are the main bottleneck here, fast I/O is always a good habit for CSES problems to prevent unexpected 
Time Limit Exceeded (TLE) errors.

**C. String Construction Alternative**
Instead of pointer math, an extremely clean C++ idiom for this problem is to build the "first half" of the 
palindrome, reverse it to get the "second half", and stick the odd character (if any) in the middle. C++ 
`std::string` constructors make this very easy.

### **4. Optimized & Cleaned Implementation**

Here is a version that maintains your $\mathcal{O}(N)$ time complexity but drastically simplifies the string 
building logic:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    vector<int> count(26, 0);
    for (char c : s) {
        count[c - 'A']++;
    }

    string first_half = "";
    char middle_char = 0;

    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 != 0) {
            // If we already found an odd character, it's invalid
            if (middle_char != 0) {
                cout << "NO SOLUTION\n";
                return 0;
            }
            middle_char = i + 'A';
        }
        
        // Append half of the occurrences of the current character to the first half.
        // If the count is odd (e.g., 3), 3/2 = 1, so 1 goes to the half, 1 stays in middle.
        first_half += string(count[i] / 2, i + 'A');
    }

    // Print the first half
    cout << first_half;
    
    // Print the middle character if it exists
    if (middle_char != 0) {
        cout << middle_char;
    }
    
    // Print the second half (which is just the first half reversed)
    reverse(first_half.begin(), first_half.end());
    cout << first_half << '\n';

    return 0;
}

```
*/