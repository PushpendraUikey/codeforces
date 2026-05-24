#include <bits/stdc++.h>
using namespace std;

int arr[1005];
void solve() {
    int n;
    cin >> n;

    for(int i=1; i<=n; i++) {
        cin >> arr[i];
    }

    int minval = INT_MAX;
    int maxval = INT_MIN;
    int total = 0;
    for(int i=1; i<=n; i++) {
        if(minval > arr[i]) minval = arr[i];
        if(maxval < arr[i]) maxval = arr[i];
        total += arr[i];
    }
    int avg = total/n;
    int ans = ( (maxval-avg) + (avg-minval) + 1)/2;
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while(tt-->0) {
        solve();
    }
}