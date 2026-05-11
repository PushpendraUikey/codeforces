#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Distinct Split
// https://codeforces.com/contest/1791/problem/D

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    unordered_map<char, int> mp, left;
    left[s[0]] = 1;

    for(int i=1; i<n; i++){
        mp[s[i]]++;
    }

    int leftsize = 1;
    int rightsize = mp.size();
    int ans = leftsize + rightsize;

    for(int i=1; i<n; i++){
        mp[s[i]]--;
        if(mp[s[i]] == 0){
                rightsize--;
        }
        if(left[s[i]] == 0){
            leftsize++;
            ans = max(ans, leftsize+rightsize);
        }
        left[s[i]] = 1;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}