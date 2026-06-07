#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/group/KQjBMkHxUY/contest/621334/problem/B

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if(!(cin>>s)) return 0;
    int len = s.length();

    vector<vector<int>> arr;
    stack<int> st;
    int i=0;
    int j=0;
    while(i<len) {
        while(i<len && s[i] == '(') {
            st.push(i+1);
            i++;
        }
        if(i<len) arr.push_back({});
        while(i<len && s[i] == ')') {
            arr[j].push_back(i+1);
            arr[j].push_back(st.top());
            st.pop();
            i++;
        }
        sort(arr[j].begin(), arr[j].end());
        j++;
    }
    cout << arr.size() << '\n';
    for(int i=0; i<arr.size(); i++) {
        cout << arr[i].size() << '\n';
        for(int j=0; j<arr[i].size(); j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}