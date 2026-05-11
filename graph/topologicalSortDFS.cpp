#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfs(vector<vector<int>>&adj, vector<bool>&visited, stack<int>&st, int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if(!visited[v]) {
            dfs(adj, visited, st, v);
        }
    }
    st.push(u);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<bool> visited(n, false);
    stack<int> toposort;
    int a, b;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
    }
    
    for (int i=0; i<n; i++) {
        if(!visited[i]) {
            dfs(adj, visited, toposort, i);
        }
    }

    while(!toposort.empty()) {
        int top = toposort.top(); 
        toposort.pop();
        cout << top << ' ';
    }
    cout << '\n';
}