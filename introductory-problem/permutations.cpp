#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1070
int main() {
    int n; 
    cin >> n;
    if(n==3 || n==2) {
        cout << "NO SOLUTION\n";
    } else{
        for (int i=2; i<=n; i+=2) {
            cout << i << ' ';
        }
        int j=1;
        for (int i=1; i<=(n+1)/2; i++, j+=2) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}