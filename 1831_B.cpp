#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Array Merging
// https://codeforces.com/contest/1831/problem/B

struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        if(a.first==b.first) return a.second > b.second;
        return a.first < b.first;
    }
};

int n;
int arr[200005];
int brr[200005];

void solve() {
    cin >> n;
    for(int i=0; i<n; i++) cin >> arr[i];
    for(int i=0; i<n; i++) cin >> brr[i];

    vector<int> fa(n+n+1, 0);
    vector<int> fb(n+n+1, 0);

    int p = 0;
    for(int i=1; i<n; i++){
        if(arr[i] != arr[i-1]){
            fa[arr[i-1]] = max(fa[arr[i-1]], i-p);
            p = i;
        }
    }
    fa[arr[n-1]] = max(fa[arr[n-1]], n-p);
    p = 0;
    for(int i=1; i<n; i++){
        if(brr[i] != brr[i-1]){
            fb[brr[i-1]] = max(fb[brr[i-1]], i-p);
            p = i;
        }
    }
    fb[brr[n-1]] = max(fb[brr[n-1]], n-p);

    int ans = 0 ;
    for(int i=1; i<=n+n; i++){
        ans = max(ans, fa[i]+fb[i]);
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