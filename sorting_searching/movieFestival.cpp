#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1629

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=-1;
    int a=-1,b=-1;
    if(!(cin >> n)) return 0;
    vector<pair<int,int>> arr(n);
    for ( int i=0; i<n; i++) {
        cin >> a >> b;
        arr[i] = {b, a};
    }

    sort(arr.begin(), arr.end());
    int lastend = -1;
    int movieWatch = 0;
    for(int i=0; i<n; i++) {
        if(lastend <= arr[i].second) {
            lastend = arr[i].first;
            movieWatch++;
        }
    }

    cout << movieWatch << '\n';
}