#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Ski Resort
// https://codeforces.com/contest/1840/problem/C

struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        if(a.first==b.first) return a.second > b.second;
        return a.first < b.first;
    }
};

int n, k, q;
int arr[200005];

void solve() {
    cin >> n >> k >> q;
    for(int i=0; i<n; i++) cin >> arr[i];

    int curr_window=0;
    ull possibility = 0;
    for(int i=0; i<n; i++) {
        if(arr[i] > q) curr_window = 0;
        else curr_window++;
        if(curr_window >= k){
            possibility = possibility + (curr_window-k+1);
        }
    }

    cout << possibility << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}