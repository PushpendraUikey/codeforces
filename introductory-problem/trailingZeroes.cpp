#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1618

int main() {
    int n; cin >> n;
    ll val = 5;
    int trailingZeros = 0;

    while(n/val) {
        trailingZeros += (n/val);
        val = val*5;
    }
    cout << trailingZeros << '\n';
}