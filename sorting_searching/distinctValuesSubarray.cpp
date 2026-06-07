#include<bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/2428

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for(int i=0; i<n; i++) cin >> arr[i];

    unordered_map<int, int, custom_hash> mp;
    long long cnt = 0;
    int left = 0;
    int distinct_count = 0;

    for(int right=0; right<n; right++) {
        int rel = arr[right];
        int lel = arr[left];
        if(mp[rel] == 0) {
            distinct_count++;
        }
        mp[rel]++;

        while(distinct_count > k) {
            lel = arr[left];
            mp[lel]--;
            if (mp[lel] == 0) {
                distinct_count--;
            }
            left++;
        }

        // All valid subarrays ending at right;
        cnt += (right-left+1);
    }
    cout << cnt << '\n';
}

/*
Issues in Your CodeWrong Logic for CSES 2428: The problem asks for subarrays with 
at most $k$ distinct values. Your code currently tracks the last seen index of 
duplicates and applies a block-sum formula, which does not solve this problem.
Integer Overflow: The total number of subarrays can be up to $\frac{n(n+1)}{2} 
\approx 2 \times 10^{10}$, which exceeds the 32-bit int limit. cnt must be 
long long.Missing Frequency Map: You need to track the frequency of elements 
in the current window to know exactly when a distinct element enters or leaves.
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    unordered_map<int, int, custom_hash> mp;
    int cnt = 0;
    int left = 0;
    int right = 0;
    while(right < n) {
        int curr = arr[right];
        if(mp.count(curr) > 0) {
            int window = right - left;
            if(window <= k) {
                cnt += (window * (window+1));
            } else {
                cnt += (2*window - k) * (k+1);
            }
            left = max(left, mp[curr]+1);
        }
        mp[curr] = right;
        right++;
    }

    cout << cnt << '\n';
}
*/