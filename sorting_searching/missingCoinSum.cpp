#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/2183
// Thought process: if a sum upto 1...k-1 can be formed using 0...i-1 then if arr[i] <= k then sum
// upto 1...arr[i] + k-1 can be formed using 0...i;
// Solution is quite tricky, actually I can form upto ans-1 sum at any given iteration, thus ans 
// represents the unformable solution. Kind of DP with some constraints given.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;
    vector<int> arr(n);
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    ll ans = 0;
    if(arr[0] == 1) {
        ans = 1;
    }else {
        cout << 1 << '\n';
        return 0;
    }
    for(int i=0; i<arr.size(); i++) {
        if(arr[i] <= ans) ans += arr[i];
        else break;
    }
    cout << ans << '\n';
}