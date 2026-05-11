#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<bool> dirvisited;
bool dfs(int c) {
    dirvisited[c] = true;
    visited[c] = true;
    for (int v : adj[c]) {
        if(!visited[v]) {
            if(dfs(v)){
                return true;
            }
        }
        else if(dirvisited[v]) {
            return true;
        }
    }
    dirvisited[c] = false;
    return false;
}
int main() {
    // code to take input
}

// https://www.geeksforgeeks.org/batch/dsa-4/track/DSASP-Graph/problem/detect-cycle-in-a-directed-graph
// Cycle detection in a directed graph using Kahn's algorithm (Topological Sort) 

class Solution {
  public:
    bool isCyclic(int V, vector<vector<int>> &edges) {
        vector<vector<int>> adj(V);
        vector<int> indegree(V, 0);
        queue<int> q;
        int m = edges.size();
        int cntNode=0;
        for(int i=0; i<m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            indegree[v]++;
        }
        
        for(int i=0; i<V; i++){
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        while(!q.empty()) {
            cntNode++;
            int u = q.front();  q.pop();
            for (int v : adj[u]) {
                indegree[v]--;
                if(indegree[v]==0) {
                    q.push(v);
                }
            }
        }
        
        return (cntNode != V);
    }
};