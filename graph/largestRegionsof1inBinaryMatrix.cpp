#include <bits/stdc++.h>
using namespace std;

/*
Given a grid of dimensions nxm containing 0's and 1's. Find the count of 1's in the largest region of 1's. 
A region of 1's is a group of 1's where two 1s can be adjacent to each other in any of the 8 directions 
( 2 horizontal, 2 vertical and 4 diagonal). 
*/

class Solution {
  public:
    int findMaxArea(vector<vector<int>>& grid) {
        // Code here
        queue<pair<int,int>> q;
        int sizex = grid.size();
        int sizey = grid[0].size();
        
        vector<vector<bool>> visited(sizex, vector<bool>(sizey, false));
        
        for(int i=0; i<sizex; i++) {
            for(int j=0; j<sizey; j++)
                if(grid[i][j] == 1) q.push({i, j});
        }
        
        int rx[] = {1, -1, 0, 0, 1, -1, 1, -1};
        int ry[] = {0, 0, 1, -1, 1, -1, -1, 1};
        
        int max1island=0;
        
        while(!q.empty()) {
            auto [cx, cy] = q.front(); q.pop();
            
            int cnt = 0;
            if(visited[cx][cy] == true) continue;
            
            queue<pair<int,int>> tq;
            tq.push({cx, cy});
            visited[cx][cy] = true;
            while(!tq.empty()) {
                auto [tcx, tcy] = tq.front(); tq.pop();
                cnt++;
                
                for(int i=0; i<8; i++) {
                    int ncx = tcx + rx[i];
                    int ncy = tcy + ry[i];
                    if(ncx >= 0 && ncx < sizex && ncy >= 0 && ncy < sizey 
                        && visited[ncx][ncy] == false && grid[ncx][ncy] == 1){
                            visited[ncx][ncy] = true;
                            tq.push({ncx, ncy});
                        }
                }
            }
            
            max1island = max(max1island, cnt);
        }
        
        return max1island;
    }
};