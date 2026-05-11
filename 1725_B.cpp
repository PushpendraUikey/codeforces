#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Basketball Together
// https://codeforces.com/problemset/problem/1725/B

int n;
ull D;
ull arr[100005];
void solve() {
    cin >> n;
    cin >> D;
    for(int i=1; i<=n; i++) cin >> arr[i];

    sort(arr+1, arr+n+1);

    int b = 1;
    int e = n;

    int totalwin = 0;
    while(b<=e){
        ull power = arr[e];
        while(power <= D && b < e){
            power += arr[e];
            b++;
        }
        if(power>D) totalwin++;
        e--;
    }

    cout << totalwin << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}