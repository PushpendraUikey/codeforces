#include <bits/stdc++.h>
using namespace std;

// inefficient solution using bfs + dfs 
class Solution {
    int dodfs(vector<vector<int>>&mat, int cnt){
        int rwx = mat.size();
        int cly = mat[0].size();
        
        queue<pair<int,int>> q;
        for(int i=0; i<rwx; i++) {
            for (int j=0; j<cly; j++) {
                if(mat[i][j] == 2){
                    q.push({i, j});
                }
            }
        }
        int rowv[4] = {-1, 0, 1, 0};
        int colv[4] = {0, 1, 0, -1};
        bool found = false;
        while(!q.empty()) {
            pair<int, int> pr = q.front(); q.pop();
            int x = pr.first; int y = pr.second;
            for(int i=0; i<4; i++) {
                int nwx = x + rowv[i];
                int nwy = y + colv[i];
                
                if(nwx<rwx && nwx>=0 && nwy<cly && nwy>=0 && mat[nwx][nwy]==1) {
                    mat[nwx][nwy] = 2;
                    found = true;
                }
            }
        }
        
        if(found) {
            cnt = cnt+1;
            return dodfs(mat, cnt);
        } else {
            bool isone=false;
            for (int i=0; i<rwx; i++) {
                for (int j=0; j<cly; j++) {
                    if(mat[i][j] == 1) {
                        isone = true;
                    }
                }
            }
            
            if(isone) return -1;
            else return cnt;
        }
    }
  public:
    int orangesRot(vector<vector<int>>& mat) {
        // code here
        return dodfs(mat, 0);
        
    }
};


// More efficient solution using only multi source bfs traversal
class Solution {
  public:
    int orangesRot(vector<vector<int>>& mat) {
        int rwx = mat.size();
        int cly = mat[0].size();
        
        queue<tuple<int,int,int>> q;
        for(int i=0; i<rwx; i++) {
            for (int j=0; j<cly; j++) {
                if(mat[i][j] == 2){
                    q.push({i, j, 1});
                }
            }
        }
        int rowv[4] = {-1, 0, 1, 0};
        int colv[4] = {0, 1, 0, -1};
        int lastlvl = 0;
        while(!q.empty()) {
            tuple<int, int, int> pr = q.front(); q.pop();
            auto [x , y , lvl] = pr;
            for(int i=0; i<4; i++) {
                int nwx = x + rowv[i];
                int nwy = y + colv[i];
                
                if(nwx<rwx && nwx>=0 && nwy<cly && nwy>=0 && mat[nwx][nwy]==1) {
                    mat[nwx][nwy] = 2;
                    q.push({nwx, nwy, lvl+1});
                    lastlvl = lvl;
                }
            }
        }
        
        bool isone=false;
        for (int i=0; i<rwx; i++) {
            for (int j=0; j<cly; j++) {
                if(mat[i][j] == 1) {
                    isone = true;
                }
            }
        }
        
        if(isone) return -1;
        else return lastlvl; 
    }
};