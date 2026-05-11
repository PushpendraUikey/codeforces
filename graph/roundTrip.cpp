#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1669
int n, m;
vector<vector<int>> adj;
vector<int> parent;
vector<bool> visited;
int cycle_start = -1;
int cycle_end = -1;
bool dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    for (int v : adj[u]) {
        if(!visited[v]) {
            if(dfs(v, u)) return true;
        }
        else if(v != p) {   // v is guaranteed to be the ancestor of u
            cycle_start = v;
            cycle_end   = u;
            return true;
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;
    adj.resize(n+1);
    parent.assign(n+1, -1);
    visited.assign(n+1, false);

    int a=-1,b=-1;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i<=n; i++) {
        if(!visited[i]) {
            if(dfs(i, -1)) {
                vector<int> cycle;
                cycle.push_back(cycle_start);
                
                int curr = cycle_end;
                while(curr != cycle_start){
                    cycle.push_back(curr);
                    curr = parent[curr];
                }
                
                // FIX 1: Push cycle_start to close the loop correctly
                cycle.push_back(cycle_start);

                cout << cycle.size() << '\n';
                for (int ele : cycle) {
                    cout << ele << ' ';
                }
                cout << '\n';
                
                // FIX 2: Terminate immediately after printing the first cycle
                return 0; 
            }
        }
    }
    
    // We only reach here if NO cycles were found anywhere
    cout << "IMPOSSIBLE\n";
    return 0;
}

/*
// Below code doesn't work because that has issues with parent pointer because it is not 
// simple backtrack rather the traversal is done level wise hence parent might go upto -1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n=-1,m=-1;
    if(!(cin>>n>>m)) return 0;
    int a=-1,b=-1;
    vector<vector<int>> adj(n+1);
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> parent(n+1, -1);
    vector<bool> visited(n+1, false);
    bool found = false;
    for (int i = 1; i<=n; i++) {
        if(!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if(!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                        parent[v] = u;
                    } else if(v != parent[u]){
                        cout << "Entered cycle\n";
                        found = true;
                        vector<int> cycle;
                        cycle.push_back(v);
                        int curr = u;
                        while(curr != v) {
                            cycle.push_back(curr);
                            curr = parent[curr];
                        }
                        cout << cycle.size() << '\n';
                        for (int ele : cycle){
                            cout << ele << ' ';
                        }
                        cout << '\n';
                        cout << "Exit Cycle\n";
                    }
                }
            }
        }
    }
    if (!found) {
        cout << "IMPOSSIBLE\n";
    }
}
*/