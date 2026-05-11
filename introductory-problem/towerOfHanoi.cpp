#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/2165

vector<pair<int,int>> tower;
void hanoi(int A, int B, int C, int n) {
    if(n==0) return;
    hanoi(A, C, B, n-1);      // moved n-1 smaller boxes to Auxilliary rod.
    tower.push_back({A,C}); // moved the nth (largest block) to destination.
    hanoi(B, A, C, n-1);      // moved n-1 blocks to destination from auxilliary rod now.
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    hanoi(1, 2, 3, n);

    int size = tower.size();
    cout << size << '\n';
    for(int i=0; i<size; i++) {
        cout << tower[i].first << ' ' << tower[i].second << '\n';
    }
}