#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1631

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    ll maxtime = -1;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        if(arr[i] > maxtime) maxtime = arr[i];
    }
    ll totaltime = accumulate(arr.begin(), arr.end(), 0LL);
    ll othertime = totaltime - maxtime;
    if(maxtime > othertime) {
        totaltime += (maxtime - othertime);
    }
    cout << totaltime << '\n';
}

/*
This sounds like the classic "Reading Books" problem from the CSES Sorting and Searching section. It's a great logic 
puzzle that relies more on a key mathematical observation than a complex data structure.

Here are three progressive hints to help you find the O(N) approach.

### **Hint 1: Identify the Key Variables**

Don't worry about simulating the exact order in which they read the books. Instead, focus on just two values from the 
input array:

1. The maximum reading time of a single book (let's call it M).
2. The sum of the reading times of all the *other* books combined (let's call it S_{other}).

### **Hint 2: Analyze the Extreme Case**

Imagine a scenario where M > S_{other}. One book is absolutely massive—taking longer to read than all the other books 
put together.

* Person A starts reading the massive book M.
* Person B starts reading the other books.
* Person B finishes *all* the other books (S_{other}) while Person A is still stuck on the first book.

What happens next? Person B has to sit idle and wait for Person A to finish M before they can swap. In this specific 
case, what is the absolute minimum time it will take for both to finish everything?

### **Hint 3: Analyze the Balanced Case**

Now imagine the opposite: M \le S_{other}. No single book dominates the collection.

In this scenario, it is always possible to perfectly schedule the reading order so that neither person ever has to sit 
idle waiting for the other to finish a book. If both readers are constantly reading without a single second of downtime, 
what does the total time equal?



It is completely normal to get tripped up by this case! It intuitively feels like a traffic jam is inevitable and that 
at *some* point, Reader A will want a book that Reader B is currently holding.

However, mathematically, if M \le S_{other}, the total time is simply **the sum of all the books (\sum t_i)**. Neither 
person ever spends a single second waiting.

To understand why this is possible, we just have to construct a specific schedule. Let's break down exactly how they 
swap books without downtime.

### The Master Schedule

Let M be the time it takes to read the largest book.
Let the rest of the books be a sequence R = [r_1, r_2, ..., r_k].
The total time to read R is S_{other}.

We know two fundamental facts:

1. **The Balanced Fact:** M \le S_{other} (The largest book is shorter than or equal to all the others combined).
2. **The Maximum Fact:** For every individual book r_i in group R, t(r_i) \le M (No single book in the rest of the 
pile is bigger than the maximum book).

Here is the perfect schedule to guarantee zero idle time:

* **Reader 1 (Alice):** Reads M first, then reads the books in R in order (r_1 \rightarrow r_2 \rightarrow ... \rightarrow r_k).
* **Reader 2 (Bob):** Reads the books in R first (r_1 \rightarrow r_2 \rightarrow ... \rightarrow r_k), and then 
reads M last.

### Why does this perfectly avoid collisions?

We only need to verify that a collision doesn't happen for the massive book (M), and that a collision doesn't happen 
for any of the smaller books (R).

**1. Collision Check for the Massive Book (M)**

* Alice starts M at time 0 and finishes at time M.
* Bob reads all the books in R first. He finishes them and is ready to start M at time S_{other}.
* Does Bob have to wait? No. Because of our *Balanced Fact* (M \le S_{other}), Alice has already finished M by the 
time Bob is ready for it.

**2. Collision Check for the Smaller Books (R)**
This is where the magic happens. Let's look at the very first small book, r_1.

* Bob starts r_1 at time 0 and finishes at time t(r_1).
* Alice is busy reading M. She won't ask for r_1 until time M.
* Because of our *Maximum Fact* (t(r_1) \le M), Bob finishes r_1 before Alice even finishes M. Bob drops it on the 
table, moves to r_2, and it's waiting for Alice when she needs it.

Does this hold up for the later books? Let's check a random book deep in the pile, r_i:

* Bob finishes r_i at time: t(r_1) + t(r_2) + ... + t(r_i).
* Alice starts r_i at time: M + t(r_1) + t(r_2) + ... + t(r_{i-1}).

For Bob to cause a traffic jam, he would have to finish r_i *after* Alice wants to start it. Mathematically, that 
overlap would look like this:
    t(r_1) + ... + t(r_i) > M + t(r_1) + ... + t(r_{i-1})

If we cancel out all the previous books (t(r_1) through t(r_{i-1})) from both sides, we are left with:
    t(r_i) > M

But wait! We defined M as the largest book in the entire collection. Therefore, t(r_i) > M is **impossible**. 
Bob will always finish reading r_i before (or exactly when) Alice reaches out to grab it.

### Bringing It All Together

Because this schedule guarantees zero waiting time, both readers read continuously from second zero until the very 
last book is finished. Therefore, the total time is simply the sum of all books: M + S_{other}.

If you combine this with the extreme case (where M > S_{other}, making the total time exactly 2M), you get a 
beautifully simple piece of logic for your C++ implementation: the answer is always just the maximum between the 
sum of all books and twice the largest book!
*/