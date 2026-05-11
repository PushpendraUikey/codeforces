#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Monsters
// https://codeforces.com/contest/1849/problem/B

struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        if(a.first==b.first) return a.second > b.second;
        return a.first < b.first;
    }
};
int n, k;
int brr[300005];
void solve() {
    cin >> n >> k;
    vector<pair<int, int>> arr;
    arr.resize(n);
    int val;
    for (int i=0; i<n; i++ ){
        cin >> val;
        arr[i] = {val, i+1};
    }

    for(int i=0; i<n; i++) {
        arr[i].first = arr[i].first%k;
        if(arr[i].first == 0) arr[i].first = k;
    }

    sort(arr.begin(), arr.end(), Compare());

    for(int i=n-1; i>=0; i--){
        cout << arr[i].second << ' ';
    }
    cout << '\n';
    // int candidate = -1;
    // for(int i=0; i<n; i++){
    //     candidate = i;
    //     if(arr[candidate].first>=k) break;
    // }
    
    // int j=0;
    // int temp = candidate;
    
    // while(temp<n && arr[temp].first == k){
    //     brr[j] = arr[temp].second;
    //     temp++;
    //     j++;
    // }
    // int temp2 = candidate - 1;
    // while(temp2 >= 0){
    //     brr[j] = arr[temp2].second;
    //     temp2--;
    //     j++;
    // }
    // while(j<n){
    //     brr[j] = arr[temp].second;
    //     temp++;
    //     j++;
    // }

    // for(int i=0;i < n; i++) {
    //     cout << brr[i] << ' ';
    // }   cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}