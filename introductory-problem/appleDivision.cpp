#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1623

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;
    vector<int> arr(n);
    for( int i=0; i<n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    ll first = 0, last=0;
    int b=0, e=n-1;
    while(b<=e) {
        if( abs(last-first-arr[b]) < abs(first-last-arr[e])) {
            first += arr[b++];
        } else {
            last += arr[e--];
        }
    }
    cout << abs(first-last) << '\n';
}