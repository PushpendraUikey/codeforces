#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1671
int n=-1,m=-1;
vector<vector<pair<int,int>>> adj;
vector<tuple<int,int,int>> edges;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n>>m)) return 0;
    edges.resize(m);
    for(int i=0; i<m; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        edges.push_back({a, c, b});
    }
    sort(edges.begin(), edges.end());
    vector<ll> dist(n+1, LLONG_MAX);
    dist[1] = 0;
    for (int i=0; i<m; i++) {
        auto [a , wt , b] = edges[i];
        
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;
    adj.resize(n+1);
    for (int i=0; i<m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll> dist(n+1, LLONG_MAX);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push({0, 1});
    dist[1] = 0;
    
    // dijktras assumes no negative cycle are present.
    while(!q.empty()) {
        pair<ll,int> currnode = q.top(); q.pop();
        int u  = currnode.second;
        ll cw = currnode.first;
        for( pair<int,int> node : adj[u] ) {
            int v = node.first;
            int w = node.second;
            if(cw + w < dist[v]) {
                dist[v] = cw + w;
                q.push({dist[v], v});
            }
        }
    }
    for (int i=1; i<=n ;i++) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}