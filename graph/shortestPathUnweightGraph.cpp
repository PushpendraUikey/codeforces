#include <bits/stdc++.h>
using namespace std;

// Grahp is given as adjacency list and it is unweighted.
// TC: O(V+E), SC: O(V)
int shortestPath(vector<vector<int>>&adj, int src) {
    int V = adj.size();
    vector<int> dist(V, -1);
    vector<int> parent(V, -1);

    queue<int> q;
    q.push(src);
    dist[src] = 0;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if(dist[v] != -1) {
                dist[v] = dist[u]+1;
                parent[v] = u;
            }
        }
    }
}