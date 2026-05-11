#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/1915/B
int arr[3][3];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    if(!(cin >> tt)) return 0;
    while(tt--) {
        int cx=-1, cy=-1;
        char ch;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++) {
                cin >> ch;
                if(ch == '?'){
                    cx = i;
                    cy = j;
                    arr[i][j] = 0;
                } else {
                    arr[i][j] = ch - 'A'+1;
                }
            }
        }
        int res = 1^2^3;
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                res ^= arr[i][j];
            }
        }
        cout << (char)('A'+res-1) << '\n';
    }
}