#include <bits/stdc++.h>
using namespace std;

int arr[200005];
int n=-1;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr+n);
    int distinctCount = 1;
    for(int i=1; i<n; i++) {
        if(arr[i] != arr[i-1]) distinctCount++;
    }

    cout << distinctCount << '\n';
}