#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/2217
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<int> eletoPos(n+1);
    vector<int> postoEle(n+1);
    int val;
    for(int i=1; i<=n; i++) {
        cin >> val;
        eletoPos[val] = i;
        postoEle[i] = val;
    }
    
    int passes = 1;
    for (int i=1; i<n; i++) {
        if(eletoPos[i+1] < eletoPos[i]){
            passes++;
        }
    }

    int a , b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        int v1 = postoEle[a];
        int v2 = postoEle[b];
        postoEle[a] = v2;
        postoEle[b] = v1;

        std::set<pair<int,int>> st;
        if(v1 < n){
            st.insert({v1, v1+1});
        }
        if(v1 > 1){
            st.insert({v1-1, v1});
        }
        if(v2 < n){
            st.insert({v2, v2+1});
        }
        if(v2 > 1){
            st.insert({v2-1, v2});
        }

        for (auto [e1, e2] : st) {
            if(eletoPos[e2] < eletoPos[e1]){
                passes--;
            }
        }
        eletoPos[v1] = b;
        eletoPos[v2] = a;

        for (auto [e1, e2] : st) {
            if(eletoPos[e2] < eletoPos[e1]){
                passes++;
            }
        }
        cout << passes << '\n';
    }
}

// Only thing to care about here was to not do the case condition checks because it might happen that 
// duplicates arise however if set is used that thing is taken care of.