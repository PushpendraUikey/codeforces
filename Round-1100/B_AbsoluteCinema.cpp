#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[100005];
int b[100005];

void solve() {
    int n; cin >> n;
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<n; i++) cin >> b[i];

    ll maxa = 0;
    ll bsum = 0;

    for(int i=0; i<n; i++) {
        if(a[i] > b[i]) {
            bsum += a[i];
            if(b[i] > maxa) maxa = b[i];
        } else {
            bsum += b[i];
            if(a[i] > maxa) maxa = a[i];
        }
    }

    ll ans = maxa + bsum;
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while(tt-->0) solve();
}