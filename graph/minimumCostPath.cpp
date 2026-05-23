#include <bits/stdc++.h>
using namespace std;

/*
Given a square grid of size N, each cell of which contains an integer cost that represents a cost to traverse 
through that cell, we need to find a path from the top left cell to the bottom right cell by which the total 
cost incurred is minimum.
From the cell (i,j) we can go (i,j-1), (i, j+1), (i-1, j), (i+1, j).  
*/

class Solution {
  public:
    // Function to return the minimum cost to react at bottom
    // right cell from top left cell.
    int minimumCostPath(vector<vector<int>>& grid) {
        // Code here
        int size = grid.size();
        vector<vector<int>> dist(size, vector<int>(size, INT_MAX));
        dist[0][0] = grid[0][0];
        
        queue<pair<int,int>> q;
        q.push({0, 0});
        
        int rx[] = {1, -1, 0, 0};
        int ry[] = {0,  0, 1, -1};
        
        while(!q.empty()) {
            auto [cx, cy] = q.front(); q.pop();
            
            for(int i=0; i<4; i++) {
                int nx = cx+rx[i];
                int ny = cy+ry[i];
                if(nx>=0 && nx<size && ny>=0 && ny<size){
                    if(dist[nx][ny] > dist[cx][cy] + grid[nx][ny]) {
                        dist[nx][ny] = dist[cx][cy]+grid[nx][ny];
                        q.push({nx, ny});
                    }
                }
            }
        }
        
        return dist[size-1][size-1];
    }
};