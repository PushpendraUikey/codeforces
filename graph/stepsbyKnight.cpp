#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        // multi source bfs will be used here
        int tx = targetPos[0]-1; int ty = targetPos[1]-1;
        int sx = knightPos[0]-1; int sy = knightPos[1]-1;
        
        int xwalk[8] = {2 , 2 , 1 , 1, -1, -1, -2, -2};
        int ywalk[8] = {1, -1 , 2, -2,  2, -2,  1, -1};
        
        queue<tuple<int,int,int>> q;
        q.push({sx, sy, 0});
        while(!q.empty()) {
            auto [x , y, step] = q.front(); q.pop();
            
            if(x == tx && y == ty) return step;
            
            for(int i=0; i<8; i++) {
                int nx = x + xwalk[i];
                int ny = y + ywalk[i];
                
                if(nx<n && nx>=0 && ny<n && ny>=0){
                    if(nx == tx && ny == ty) {
                        return step+1;
                    }
                    q.push({nx, ny, step+1});
                }
            }
        }
        
        return -1;
    }
};


// Efficient solution using bfs with visited array
class Solution {
  public:
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        // multi source bfs will be used here
        int tx = targetPos[0]-1; int ty = targetPos[1]-1;
        int sx = knightPos[0]-1; int sy = knightPos[1]-1;
        
        int xwalk[8] = {2 , 2 , 1 , 1, -1, -1, -2, -2};
        int ywalk[8] = {1, -1 , 2, -2,  2, -2,  1, -1};
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<tuple<int,int,int>> q;
        q.push({sx, sy, 0});
        visited[sx][sy] = true;
        
        while(!q.empty()) {
            auto [x , y, step] = q.front(); q.pop();
            
            if(x == tx && y == ty) return step;
            
            for(int i=0; i<8; i++) {
                int nx = x + xwalk[i];
                int ny = y + ywalk[i];
                
                if(nx<n && nx>=0 && ny<n && ny>=0 && !visited[nx][ny]){
                    if(nx == tx && ny == ty) {
                        return step+1;
                    }
                    visited[nx][ny] = true;
                    q.push({nx, ny, step+1});
                }
            }
        }
        
        return -1;
    }
};