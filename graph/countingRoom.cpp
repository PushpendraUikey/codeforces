#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<char>>&grid, int x, int y) {
    int sizex = grid.size();
    int sizey = grid[0].size();
    queue<pair<int,int>> q;
    q.push({x, y});
    int rwx[4] = {0 , 0 , 1, -1};
    int cly[4] = {1 ,-1 , 0,  0};
    while(!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        for(int i=0; i<4; i++) {
            int nx = cx + rwx[i];
            int ny = cy + cly[i];
            if(nx<sizex && nx>=0 && ny<sizey && ny>=0 && grid[nx][ny] == '.') {
                grid[nx][ny] = '$';
                q.push({nx, ny});
            }
        }
    }
}
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i<n ; i++) {
        for (int j = 0; j<m; j++) {
            cin >> grid[i][j];
        }
    }

    int countRooms = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(grid[i][j] == '.'){
                grid[i][j] = '$';
                countRooms++;
                solve(grid, i, j);
            }
        }
    }

    cout << countRooms <<'\n';

}