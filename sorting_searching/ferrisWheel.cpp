#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1090
long long n=-1, x=-1;
int arr[200005];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n>>x)) return 0;
    for (int i=0; i<n; i++) cin >> arr[i];
    sort(arr, arr+n);
    int gondola = 0;
    long long sum = 0;
    int b=0, e=n-1;
    while(b<e) {
        sum = arr[b] + arr[e];
        if(sum<=x) {
            gondola++;
            b++; e--;
        }else{
            e--;
            gondola++;
        }
    }
    if(b<=e) gondola++;
    cout << gondola << '\n';
}