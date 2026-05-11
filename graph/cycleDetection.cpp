#include <bits/stdc++.h>
using namespace std;

bool dfsUtil(vector<vector<int>>&adj, vector<bool>&visited, int node, int parent) {
    visited[node] = true;
    for(auto v : adj[node]) {
        if(!visited[v]) {
            if(dfsUtil(adj, visited, v, node))
                return true;
        } else if(v != parent){
            return true;
        }
    }
    return false;
}
bool dfsCycleDetect(vector<vector<int>>&adj) {
    int V = adj.size();
    vector<bool> visited(V, false);

    for(int i = 0 ; i < V ; i++ ) {
        if (!visited[i]) {
            if(dfsUtil(adj, visited, i, -1)) 
                return true;
        }
    }
    return false;
}

bool bfsCycleDetect(vector<vector<int>> &adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    
    for (int i = 0; i < V; i++) {
        if(!visited[i]) {
            queue<pair<int,int>> q;
            q.push({i, -1});
            visited[i] = true;
            while(!q.empty()) {
                auto [u , p] = q.front(); q.pop();
                for (auto v : adj[u]) {
                    if(!visited[v]) {
                        visited[v] = true;
                        q.push({v, u});
                    } else if(v != p) {
                        return true;
                    }
                }
            }
        }

    }
    return false;
}

/*

bool dfsUtil(vector<vector<int>>&adj, vector<bool>&visited, int node, int parent) {
    visited[node] = true;
    for(auto v : adj[node]) {
        if(!visited[v]) {
            return dfsUtil(adj, visited, v, node);
        } else if(v != parent){
            return true;
        }
    }
    return false;
}
bool dfsCycleDetect(vector<vector<int>>&adj) {
    int V = adj.size();
    vector<bool> visited(V, false);

    for(int i = 0 ; i < V ; i++ ) {
        if (!visited[i] && dfsUtil(adj, visited, i, -1)) {
            return true;
        }
    }
    return false;
}

Yes, there is a subtle but fatal flaw in this logic! It will actually report **false positives**—meaning it will 
say there is a cycle in completely normal graphs (like a straight line) that don't have one.

The bug is hiding in how C++ evaluates the `if / else if` block combined with the `&&` operator.

### 🐛 The Trap of the `else if`

Let's look closely at your loop inside the DFS:
```cpp
if(!visited[v] && dfs(adj, visited, v, node)){
    return true;
} else if(v != parent) {
    return true;
}
```

**Here is exactly how it fails:**
Imagine you are exploring a straight line graph: **`A --- B --- C`**. There are no cycles here.

1.  You start at **A**. You check neighbor **B**. **B** is unvisited.
2.  The code evaluates `!visited[B]` (True) and calls `dfs(B)`.
3.  Inside `dfs(B)`, you check neighbor **C**. **C** is unvisited.
4.  The code evaluates `!visited[C]` (True) and calls `dfs(C)`.
5.  Inside `dfs(C)`, there are no more new neighbors. It returns `false`.
6.  **Here is the critical moment:** Back inside `dfs(B)`, the statement `dfs(C)` evaluated to `false`. 
Therefore, the entire condition `(!visited[C] && dfs(C))` evaluates to **`false`**.
7.  Because that `if` statement failed, the code moves to the `else if(v != parent)`. 
8.  It checks: Is **C** (the neighbor we just checked) not equal to **A** (the parent of **B**)? Yes, 
**C != A**.
9.  The code incorrectly hits `return true;` and falsely reports a cycle!

### 🛠️ The Fix: Separate the Concerns

The issue is that the `else if` acts as a fallback for the *entire* first statement. You only want to check 
`v != parent` if the node was **already visited**. If it was unvisited, but its DFS path just happened to be 
a dead end, you should do nothing and move to the next neighbor.

To fix this, you must explicitly separate the "is it visited?" check from the "did the recursive call find a 
cycle?" check.

Here is the corrected `dfs` function:

```cpp
bool dfs(vector<vector<int>>& adj, vector<bool>& visited, int node, int parent) {
    visited[node] = true;
    
    for (auto v : adj[node]) {
        // Condition 1: The node has NOT been visited yet
        if (!visited[v]) {
            // Explore it. If it finds a cycle, propagate 'true' upwards.
            if (dfs(adj, visited, v, node)) {
                return true;
            }
            // Notice there is no 'else' here. If dfs returns false, 
            // we just let the loop continue to the next neighbor.
        } 
        // Condition 2: The node HAS been visited, AND it is not the parent
        else if (v != parent) {
            return true;
        }
    }
    return false;
}
```
### 💡 Key Takeaway
While short-circuiting with `&&` is elegant, you have to be very careful when attaching `else` or `else if` blocks 
to them. If the first part of the `&&` is true, but the second part is false, it forces the code into the `else` 
block when you might not want it to go there!
*/