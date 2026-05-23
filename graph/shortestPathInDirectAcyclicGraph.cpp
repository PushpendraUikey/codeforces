#include <bits/stdc++.h>
using namespace std;

// Following here's the topological sort using dfs then finding shortest path in DAG.
void dfsTopoSort(vector<vector<pair<int,int>>>&adj, vector<bool>&visited, stack<int>&st, int node) {
    visited[node] = true;

    for(auto [v, wt] : adj[node]) {
        if(visited[v] == false) {
            dfsTopoSort(adj, visited, st, v);
        }
    }

    st.push(node);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;
    vector<vector<pair<int,int>>> adj(V);
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    stack<int> st;

    dist[0] = 0; // considering `0` as a source, it can be anything else

    for(int i=0; i<E; i++) {
        int a, b , wt;
        cin >> a >> b >> wt;
        adj[a].push_back({b, wt});
    }

    for(int i=0; i<V; i++) {
        if(visited[i] == false) {
            dfsTopoSort(adj, visited, st, i);
        }
    }

    while(!st.empty()) {
        int node = st.top(); st.pop();
        if(dist[node] == INT_MAX) continue;
        for(auto [v, wt] : adj[node]) {
            if(dist[node]+wt < dist[v]) {
                dist[v] = dist[node] + wt;
                // no need to push `v` to stack as it already has everything in Topological order.
            }
        }
    }

    cout << "Distance from source 0 to all other nodes is: \n";
    for(int i=0; i<V; i++) {
        cout << "To node " << i << " : dist " << dist[i] << '\n';
    }
}
// Following here's the Kahn's approach to find the shortest path in a directed acyclic graph (DAG) in O(V+E) 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;
    vector<vector<pair<int,int>>> adj(V);
    vector<int> indegree(V, 0);
    vector<int> dist(V, INT_MAX);
    queue<int> q;

    dist[0] = 0; // considering `0` as a source, it can be anything else

    for(int i=0; i<E; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        adj[a].push_back({b, wt});
        indegree[b]++;
    }

    for(int i=0; i<V; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto [v, wt] : adj[u]) {
            if(dist[u] != INT_MAX && dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
            }
            // We need to always reduce the indegree of each processed neighbor.
            indegree[v]--;
            if(indegree[v] == 0){
                q.push(v);  // essential to get the topological order of DAG.
            }
        }
    }

    cout << "Distance from source 0 to all other nodes is: \n";
    for(int i=0; i<V; i++) {
        cout << "To node " << i << " : dist " << dist[i] << '\n';
    }
}