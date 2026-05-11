#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Minimum LCM
// https://codeforces.com/problemset/problem/1765/M

ll n;
void solve() {
    cin >> n;

    ll a = 1;
    for(ll g = 2; g*g <=n ; g++){
        if(n%g==0){
            a = n/g;
            break;
        }
    }
    cout << a << " " << n - a << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}