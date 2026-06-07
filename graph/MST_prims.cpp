#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll findMSTefficient(vector<vector<pair<int,int>>>&adj, int V) {
    ll mstWeight = 0;
    vector<bool> inMST(V+1, false);
    
    // Min heap to find min weightage cut in O(log(V))
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 1});

    while(!pq.empty()) {
        auto [wt, u] = pq.top(); pq.pop();

        if(inMST[u]) continue; 

        inMST[u] = true;
        mstWeight += wt;

        for(auto [v, edge_wt] : adj[u]) {
            if(inMST[v] == false){
                pq.push({edge_wt, v});
            }
        }
    }

    cout << "Weight of MST is : " << mstWeight << '\n';
    return mstWeight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    int a, b, w;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    int mstweight = 0;
    vector<int> key(n + 1, INT_MAX);
    vector<bool> inMST(n + 1, false);

    key[1] = 0;

    // O(V2) algorithm, finding min with another loop.
    for (int count = 1; count <= n; count++) {
        int minwtU = -1;
        for (int i = 1; i <= n; i++) {
            if (inMST[i] == false && (minwtU == -1 || key[i] < key[minwtU])) {
                minwtU = i;
            }
        }

        inMST[minwtU] =
            true;  // bring it to the mst, this is the min weighted cut
        mstweight += key[minwtU];  // calculating the min weight of spanning
                                   // tree simultaneously

        for (auto [v, wt] : adj[minwtU]) {
            if (inMST[v] == false && key[v] > wt) {
                key[v] = wt;
            }
        }
    }

    cout << "Weight of MST is : " << mstweight << '\n';
}

