#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1645

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    stack<int> st;
    
    for (int i=0; i<n; i++) cin >> arr[i];
    
    for (int i=0; i<n; i++) {
        while(!st.empty()) {
            if(arr[i] <= arr[st.top()]) {
                st.pop();
            }else break;
        }
        if(st.empty()){
            cout << 0 << ' ';
        }
        else {
            cout << st.top() + 1 << ' ';
        }
        st.push(i);
    }
    cout << '\n';
}