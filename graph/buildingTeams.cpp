#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1668

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=-1, m=-1;
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> arr(n+1);
    int a=-1, b=-1;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        arr[a].push_back(b);
        arr[b].push_back(a);
    }
    vector<int> color(n+1, -1);
    
    for(int i=1; i<=n; i++) {
        if(color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while(!q.empty()) {
                int u = q.front();  q.pop();
                int clr = color[u];
                for (int v : arr[u]) {
                    if(color[v] == -1) {
                        color[v] = (clr+1)%2;
                        q.push(v);
                    } else if (color[v] == clr){
                        cout << "IMPOSSIBLE\n";
                        return 0;
                    }
                }
            }
        }
    }
    
    for(int i=1; i<=n; i++) {
        cout << color[i] + 1 << ' ' ;
    }
    cout << '\n';
}