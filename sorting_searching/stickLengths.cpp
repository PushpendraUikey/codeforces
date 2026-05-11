#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1074
// Absolute Distance is always minimized around the `median`.

int main() {
    int n;
    if(!(cin >> n)) return 0;
    vector<int> arr(n);
    ll total = 0;
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    if(n==1) {
        cout << 0 << '\n';
        return 0;
    }

    sort(arr.begin(), arr.end());

    if(n&1) {
        total = arr[n/2];
    } else {
        total = (arr[n/2]+arr[n/2-1]) / 2;
    }

    ll cost = 0;
    for(int i=0; i<n; i++) {
        cost += abs(total-arr[i]);
    }
    cout << cost << '\n';
}