#include <bits/stdc++.h>
using namespace std;

int n=-1, m=-1;
vector<vector<int>> adj;
vector<int> indegree;
vector<int> topological;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;

    adj.resize(n+1);
    indegree.assign(n+1, 0);

    for (int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }
    queue<int> q;
    for (int i=1; i<=n; i++) {
        if(indegree[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        topological.push_back(u);
        for (int v : adj[u] ) {
            indegree[v]--;
            if(indegree[v]==0){
                q.push(v);
            }
        }
    }
    for (int i=0; i<n; i++) {
        cout << topological[i] << ' ';
    }
    cout << '\n';
}