#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1754

void solve() {
    int a, b;
    if(!(cin>>a>>b)) return;
    
    if((a==0 && b>0) || (b==0 && a>0)) {
        cout << "NO\n";
        return;
    }
    if((a+b)%3==0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt; 
    if(!(cin>>tt)) return 0;
    while(tt--) {
        solve();
    }
}