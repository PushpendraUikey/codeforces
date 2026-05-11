#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1667

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=-1, m=-1;
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> CompConn(n+1);
    int a=-1, b=-1;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        CompConn[a].push_back(b);
        CompConn[b].push_back(a);
    }
    vector<int> parent(n+1, -1);
    vector<bool> visited(n+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    bool found = false;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u==n) {
            found = true;
            break;
        }
        for(int v : CompConn[u]) {
            if(!visited[v]) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }

    if(!found) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> route;
    int currcomp = n;
    while(currcomp != -1) {
        route.push_back(currcomp);
        currcomp = parent[currcomp];
    }
    cout << route.size() << '\n';
    for(int i = route.size()-1; i>=0; i--) {
        cout << route[i] << ' ';
    }
    cout << '\n';
}