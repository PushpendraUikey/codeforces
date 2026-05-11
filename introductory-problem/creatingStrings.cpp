#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1622

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int n;
    if(!(cin>>s)) return 0;
    n = s.length();

    sort(s.begin(), s.end());
    set<int> distinct;
    for(int i=1; i<n; i++) {
        if(s[i-1] != s[i]){
            distinct.insert(i);
        }
    }

    while(!distinct.empty()) {
        auto it = distinct.rbegin();
        int indx = *it;
        while(indx < n-1) {
            swap(s[indx], s[indx+1]);
            cout << s << '\n';
            indx++;
        }
    }
}