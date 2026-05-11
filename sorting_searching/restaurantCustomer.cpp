#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1619

int n = -1;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    int a=-1,b=-1;
    int i=0;
    vector<pair<int,int>> arr(2*n);
    while(i < 2*n) {
        cin >> a >> b;
        arr[i++] = {a , 1};
        arr[i++] = {b , -1};
    }
    sort(arr.begin(), arr.end());
    int currCust=0, maxCust=0;
    for(int i=0; i<2*n; i++) {
        currCust += arr[i].second;
        if(currCust > maxCust) maxCust = currCust;
    }

    cout << maxCust << '\n';
}