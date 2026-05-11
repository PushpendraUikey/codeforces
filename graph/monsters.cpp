#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1194

int n=-1, m=-1;
int sx=0,sy=0;
vector<string> grid;
set<pair<int,int>> monsterPos;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;
    grid.resize(n);
    for (int i=0; i<n; i++) {
        cin >> grid[i];
        for (int j=0; j<m; j++) {
            if(grid[i][j] == 'A'){
                sx=i;
                sy=j;
            }
            else if(grid[i][j] == 'M') {
                
            }
        }
    }
}