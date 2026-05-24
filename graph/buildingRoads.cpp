#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n = 1, m = 1;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> conncomp;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            conncomp.push_back(i);
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
        }
    }
    cout << conncomp.size() - 1 << '\n';
    for (int i = 1; i < conncomp.size(); i++) {
        cout << conncomp[i - 1] << ' ' << conncomp[i] << '\n';
    }
}