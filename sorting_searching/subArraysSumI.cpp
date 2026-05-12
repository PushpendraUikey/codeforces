#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1660
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll  x;
    ll  currsum = 0;
    int cnt = 0;
    if (!(cin >> n >> x)) return 0;
    vector<int>             arr(n);
    unordered_map<ll, bool> mp;
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i=0; i<n; i++) {
        currsum += arr[i];
        if(currsum == x) {
            cnt++;
        }
        ll rem = currsum - x;
        if(mp[rem]){
            cnt++;
        }
        mp[currsum] = true;
    }

    cout << cnt << '\n';
}