#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007

// https://cses.fi/problemset/task/1617

int main() {
    ll n;
    cin >> n;
    ll val = 2;
    ll ans = 1;
    while(n) {
        if(n&1) {
            ans = (ans * val) % mod;
        }
        val = (val * val) % mod;
        n = n >> 1;
    }
    cout << ans << '\n';
}