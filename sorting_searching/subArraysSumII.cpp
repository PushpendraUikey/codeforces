#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1661

// This custom hash randomly shifts the values, making collisions impossible to predict
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

    int n;
    ll x;
    if(!(cin>> n >> x)) return 0;

    ll currsum = 0;
    ll cnt=0;
    unordered_map<ll, int, custom_hash> mp;
    mp[0] = 1;

    for(int i=0; i<n; i++) {
        int val;
        cin >> val;
        currsum += val;
        ll rem = currsum - x;
        if(mp.count(rem) > 0) {
            cnt += mp[rem];
        }
        mp[currsum]++;
    }

    cout << cnt << '\n';
}