#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Traffic Light
// https://codeforces.com/problemset/problem/1744/C

int n;
char c;
void solve() {
    string str;
    cin >> n;
    cin >> c;
    cin >> str;

    if(c == 'g') {
        cout << 0 << '\n';
    }else{
        int maxlen = 1;
        int charidx = -1;
        int greenidx = -1;

        for(int i=0; i<n; i++){
            if(charidx==-1){
                if(str[i] == c) charidx = i;
            }else if(str[i]=='g'){
                maxlen = max(maxlen, i-charidx);
                charidx = -1;
            }
        }
        if(charidx >= 0){
            for(int i=0; i<n; i++){
                if(str[i] == 'g'){
                    greenidx = i;
                    break;
                }
            }
            maxlen = max(maxlen, (n-charidx + greenidx));
        }

        cout << maxlen << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}