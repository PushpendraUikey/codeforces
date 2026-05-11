#include <bits/stdc++.h>
using namespace std;

class Solution {
    int nearestDist(vector<vector<int>>& grid, int px, int py) {
        vector<pair<int, int>> dirn = { {1,0}, {0,1}, {0,-1}, {-1, 0},
            {1,1}, {1,-1}, {-1,-1}, {-1,1}};
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        int j = 1;
        function<int()> calculate = [&]{
            bool outofBound = true;
            for(int i=0; i<8; i++) {
                int x = dirn[i].first;
                int y = dirn[i].second;
                int nwx = x + px;
                int nwy = y + py;
                if (nwx<sizex && nwy<sizey &&
                    nwx>=0   && nwy>=0){
                    outofBound = false;
                    if(grid[nwx][nwy] == 1){
                        return abs(x) + abs(y);
                    }
                }
            }
            if(outofBound) return -1;
            for(int i=0; i<8; i++) {
                dirn[i].first = dirn[i].first/j * (j+1);
                dirn[i].second = dirn[i].second/j * (j+1);
            }
            j++;
            return calculate();
        };
        
        return calculate();
    }
  public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        // code here
        int sizex = grid.size();
        int sizey = grid[0].size();
        vector<vector<int>> matrix(sizex, vector<int>(sizey,0));

        for(int i=0; i<sizex; i++) {
            for (int j=0; j<sizey; j++) {
                if(grid[i][j] == 1) {
                    matrix[i][j] = 0;
                } else{
                    matrix[i][j] = nearestDist(grid, i, j);
                }
            }
        }
        return matrix;
    }
};


class Solution {
    struct pair_hash{
        inline size_t operator()(const pair<int,int> &v) const {
            return v.first*31+v.second;
        }
    };
    
    int nearestDist(vector<vector<int>>& grid, int px, int py) {
        vector<pair<int, int>> dirn = { {1,0}, {0,1}, {0,-1}, {-1, 0}};
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        unordered_map<pair<int,int>, bool, pair_hash> visited;
        queue<pair<int,int>> q;
        q.push({px, py});
        visited[{px, py}] = true;
        while(!q.empty()) {
            pair<int,int> pr = q.front(); q.pop();
            int cx = pr.first; int cy = pr.second;
            if(grid[cx][cy] == 1){
                visited.clear();
                return abs(px-cx)+abs(py-cy);
            }
            
            for(int i=0; i<4; i++) {
                int x = dirn[i].first;
                int y = dirn[i].second;
                int nwx = x + cx;
                int nwy = y + cy;
                if (nwx<sizex && nwy<sizey &&
                    nwx>=0   && nwy>=0){
                    if(!visited[{nwx, nwy}]){
                        q.push({nwx, nwy});
                        visited[{nwx, nwy}] = true;
                    }
                }
            }
        }
        
        return -1;
    }
  public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        // code here
        int sizex = grid.size();
        int sizey = grid[0].size();
        vector<vector<int>> matrix(sizex, vector<int>(sizey,0));
        
        for(int i=0; i<sizex; i++) {
            for (int j=0; j<sizey; j++) {
                if(grid[i][j]==1){
                    matrix[i][j] = 0;
                } else {
                    matrix[i][j] = nearestDist(grid, i, j);
                }
            }
        }
        return matrix;
    }
};


// correct and efficient solution to do multi source bfs
class Solution {
  public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        vector<vector<int>> dist(sizex, vector<int>(sizey, -1));
        queue<pair<int,int>> q;
        for(int i=0; i<sizex; i++) {
            for (int j=0; j<sizey; j++) {
                if(grid[i][j] == 1){
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        
        int rw[4] = {-1, 0, 1, 0};
        int cl[4] = {0, 1, 0, -1};
        
        while(!q.empty()) {
            pair<int,int> pr = q.front(); q.pop();
            int x = pr.first; int y = pr.second;
            
            for(int i=0; i<4; i++){
                int nx = x + rw[i];
                int ny = y + cl[i];
                if(nx<sizex && nx>=0 && ny<sizey && ny>=0 && dist[nx][ny] == -1) {
                    q.push({nx, ny});
                    dist[nx][ny] = dist[x][y] + 1;
                }
            }
        }
        
        return dist;
    }
};