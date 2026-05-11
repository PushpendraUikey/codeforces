#include <bits/stdc++.h>
using namespace std;

class Solution {
    void bfs(int x, int y, vector<vector<char>>&grid, vector<vector<bool>>&visited) {
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        int rwx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
        int cly[8] = {1,-1, 1, 0,-1,  1,  0, -1};
        
        queue<pair<int,int>> q;
        q.push({x, y});
        visited[x][y] = true;
        
        while(!q.empty()) {
            auto [cx, cy] = q.front(); q.pop();
            for(int i=0; i<8; i++) {
                int nwx = cx + rwx[i];
                int nwy = cy + cly[i];
                
                if(nwx<sizex && nwx>=0 && nwy<sizey && nwy>=0 && 
                    !visited[nwx][nwy] && grid[nwx][nwy] == 'L') {
                    q.push({nwx, nwy});
                    visited[nwx][nwy] = true;
                }
            }
        }
        
    }
  public:
    int countIslands(vector<vector<char>>& grid) {
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        vector<vector<bool>> visited(sizex, vector<bool>(sizey, false));
        int connComp = 0;
        for(int i=0; i<sizex; i++) {
            for (int j=0; j<sizey; j++) {
                if(grid[i][j] == 'L' && !visited[i][j]) {
                    bfs(i, j, grid, visited);
                    connComp++;
                }
                visited[i][j] = true;
            }
        }
        
        return connComp;
    }
};