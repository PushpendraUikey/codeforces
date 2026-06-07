#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1673
int n=-1,m=-1;
vector<vector<pair<int,int>>> adj;
vector<bool> visited;
vector<bool> dfsvisited;
vector<ll>   dist;
bool nvisited   = false;
bool cycleFound = false;

bool dfs(int u) {
    dfsvisited[u] = true;
    visited[u]    = true;
    if (u == n) {
         nvisited = true;
    }
    for (pair<int,int> node : adj[u]) {
        int v = node.first;
        int wt = node.second;
        if(dist[u] + wt > dist[v]) {
            dist[v] = dist[u] + wt;
        }
        if(dfsvisited[v]) {
            cycleFound = true;
        }
        if(!visited[v]) {
            if(!dfs(v)) {
                return false;
            }
        }
    }

    dfsvisited[u] = false;
    if(cycleFound && nvisited) return false;
    cycleFound = false;
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;

    adj.resize(n+1);
    visited.resize(n+1, false);
    dfsvisited.resize(n+1, false);
    dist.resize(n+1, LLONG_MIN);
    nvisited = false;

    for (int i=0; i<m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        adj[a].push_back({b,x});
    }
    dist[1] = 0;
    priority_queue<pair<ll,int>> q;
    q.push({0, 1});

    while(!q.empty()) {
        auto [wt, u] = q.top(); q.pop();
        
    }
    if(dfs(1)) {
        cout << dist[n] << '\n';
    } else{
        cout << -1 << '\n';
    }

}