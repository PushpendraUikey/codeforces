#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/1915/A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    if(!(cin>>tt)) return 0;
    while(tt--) {
        int a, b, c;
        if(!(cin>> a >> b >> c)) continue;
        int res = 0;
        res = a ^ b ^ c;
        cout << res << '\n';
    }
}