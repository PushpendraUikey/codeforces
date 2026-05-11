#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1640
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n=-1,x=-1;
    if(!(cin>>n>>x)) return 0;
    vector<pair<int,int>> arr(n);
    int val=-1;
    for(int i=0; i<n; i++) {
        cin >> val;
        arr[i] = {val, i+1};
    }
    sort(arr.begin(), arr.end());
    int s = 0, e = n-1;
    int a=-1, b=-1;
    while(s<e){
        int sum = arr[s].first + arr[e].first;
        if(sum == x) {
            a = arr[s].second;
            b = arr[e].second;
            break;
        } else if (sum > x) {
            e--;
        } else {
            s++;
        }
    }
    if(a==-1) {
        cout << "IMPOSSIBLE\n";
    } else{
        if(a>b) swap(a,b);
        cout << a << ' ' << b << '\n';
    }
}