#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Beautiful Array
// https://codeforces.com/problemset/problem/1715/B

int n;
ll k;
ll b;
ll s;
void solve() {
    cin >> n >> k >> b >> s;
    
    ull uplimit = (1LL * k * b) + (1LL * n * (k-1));
    ull lolimit = (1LL * k * b);

    if(s < lolimit || s > uplimit){
        cout << -1 << '\n';
    }else{
        ull rem = s - lolimit;
        ull accum = 0;

        // Optimized version should not contain any conditionals inside the loop
        // Bad practice
        for(int i=1; i<n ; i++) {
            cout << min(rem, 1ULL * (k-1))<< ' ';
            if(rem>=k-1){
                rem -= (k-1);
            }else{
                rem = 0;
            }
        }
        cout << lolimit + rem << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt; 
    cin >> tt;
    while(tt--) solve();
}