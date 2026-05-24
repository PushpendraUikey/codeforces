#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1671
int n=-1,m=-1;
vector<vector<pair<int,int>>> adj;

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

        if(cw > dist[u]) continue; // Lazy Deletion Check. Always remember to keep checking this.
        
        for( pair<int,int> node : adj[u] ) {
            int v = node.first;
            ll w = node.second;
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

/*
The bottleneck in your implementation is **processing stale nodes** in the priority queue, which will cause a 
Time Limit Exceeded (TLE) on stricter CSES test cases.

Because C++'s `std::priority_queue` does not support a `decrease_key` operation, your code simply pushes a new 
`{distance, node}` pair into the queue every time a shorter path is found. This means a single node might be 
pushed into the queue multiple times with different distances.

When you pop a node, you immediately iterate over its adjacency list `adj[u]`. If you pop an outdated (stale) 
distance for a node you've already processed with a shorter distance, you end up re-relaxing all of its edges 
unnecessarily.

## The Fix: Lazy Deletion

You can fix this by adding a single line to check if the popped distance is greater than the currently known 
shortest distance. If it is, you simply ignore it.

```cpp
while(!q.empty()) {
    pair<ll,int> currnode = q.top(); q.pop();
    int u  = currnode.second;
    ll cw = currnode.first;

    // THE FIX: Ignore stale pairs
    if (cw > dist[u]) continue; 

    for( pair<int,int> node : adj[u] ) {
        int v = node.first;
        ll w = node.second;
        if(cw + w < dist[v]) {
            dist[v] = cw + w;
            q.push({dist[v], v});
        }
    }
}

```

This is called "lazy deletion" and keeps the algorithm running in $O((V+E) \log E)$ time.

---

## The Alternative: Using `std::set`

If you want to avoid pushing duplicates into the queue altogether, you can use a `std::set` instead of a 
`std::priority_queue`.

A `set` maintains its elements in sorted order. When you find a shorter path, you can explicitly find and `erase` 
the old distance from the set before inserting the new one. This acts as a true `decrease_key` operation.

```cpp
set<pair<ll, int>> s;
dist[1] = 0;
s.insert({0, 1});

while(!s.empty()) {
    // Extract the minimum element
    auto it = s.begin();
    int u = it->second;
    ll cw = it->first;
    s.erase(it);

    for(auto [v, w] : adj[u]) {
        if(cw + w < dist[v]) {
            // Remove the old distance if it was already in the set
            if(dist[v] != LLONG_MAX) {
                s.erase({dist[v], v});
            }
            
            // Update and insert the new distance
            dist[v] = cw + w;
            s.insert({dist[v], v});
        }
    }
}

```

### Which should you use?

| Approach | Queue/Set Max Size | Practical Performance |
| --- | --- | --- |
| **`priority_queue` + Lazy Deletion** | $E$ | **Faster.** Lower constant factor (array-based heap). |
| **`set` (decrease-key)** | $V$ | **Slower.** Higher overhead due to tree rebalancing and pointer allocations. |

In competitive programming contexts like CSES, **always use the `priority_queue` with the lazy deletion check**. 
It is significantly faster in practice despite the queue temporarily growing larger than $V$.
*/