#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://www.geeksforgeeks.org/batch/dsa-4/track/DSASP-Graph/problem/mother-vertex

/*
Given a directed graph with V vertices labeled from 0 to V-1 and a list of edges edges[][], where each edge is 
represented as [u, v] indicating a directed edge from vertex u to vertex v, find a Mother Vertex of the graph.
A Mother Vertex is a vertex from which all other vertices can be reached.
If multiple such vertices exist, return the one with the smallest value.
If no such vertex exists, return -1.
*/

class Solution {
  public:
    int findMotherVertex(int V, vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        vector<bool> processed(V, false);
        
        int m = edges.size();
        for (int i=0; i<m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
        }
        
        for(int i=0; i<V; i++) {
            if(!processed[i]) {
                vector<bool> visited(V, false);
                processed[i] = true;
                visited[i] = true;
                int cntnode = 0;
                queue<int> q;
                q.push(i);
                while(!q.empty()) {
                    int u = q.front(); q.pop();
                    cntnode++;
                    
                    for(int v : adj[u]) {
                        if(!visited[v]) {
                            visited[v] = true;
                            processed[v] = true;
                            q.push(v);
                        }
                    }
                }
                if(cntnode==V){
                    return i;
                }
            }
        }
        return -1;
    }
};

/*
Gemini's Insight:

Your code is an excellent attempt, and honestly, your deduction with the `processed` array is mathematically brilliant.
You correctly realized that if node $A$ reaches node $B$, and $A$ is not a mother vertex, then $B$ cannot be a mother 
vertex either.

However, if you submit this to GeeksForGeeks or a similar competitive programming platform, it will fail with a 
**Time Limit Exceeded (TLE)** error.

Here is a review of why your logic hits a performance wall, and how to rewrite it to the industry-standard $O(V+E)$ 
approach.

### 🚨 The Bottleneck: Re-traversing Nodes

While your `processed` array prevents you from *starting* a new BFS from a failed node, it **does not stop an 
active BFS from exploring it again.**

Look at this inner loop:

```cpp
for(int v : adj[u]) {
    if(!visited[v]) { // <-- The culprit
        visited[v] = true;
        processed[v] = true;
        q.push(v);
    }
}

```

Because `visited` is newly created and initialized to `false` for every outer loop iteration, your BFS will blindly 
march through nodes that are already marked `processed`.

**The Worst-Case Scenario:**
Imagine a straight line graph: $V_{n} \to V_{n-1} \to \dots \to V_1 \to V_0$.

* **i = 0:** BFS visits $0$. `cntnode` = 1.
* **i = 1:** BFS visits $1 \to 0$. `cntnode` = 2.
* **i = 2:** BFS visits $2 \to 1 \to 0$. `cntnode` = 3.

Even though you mark them as `processed`, the next BFS completely ignores that fact and re-traverses the entire chain. 
This results in $1 + 2 + 3 \dots + V$ operations, making your time complexity **$O(V^2)$**. For $10^5$ vertices, 
that is $10^{10}$ operations, which will instantly TLE.

---

### 🛠️ The Fix: Kosaraju's Candidate Algorithm

To solve this in pure **$O(V+E)$** time, we use a trick derived from Kosaraju’s Algorithm for Strongly Connected 
Components.

**The Theory:**

1. If you run a standard DFS on a graph, the **very last vertex to finish processing** is the *only* possible 
    candidate to be a Mother Vertex.
2. Why? Because if a Mother Vertex exists, it must be at the "source" of the graph. No unvisited nodes can reach it, 
    so it will only be visited when the outer loop explicitly calls DFS on it.
3. **The Smallest Value Trick:** Because the loop runs from `0` to `V-1`, the outer loop will naturally hit the 
    *smallest* member of the source component first. That node will then sweep through the rest of the graph, 
    making it the very last node to finish in the entire algorithm!

### ✅ The Optimized $O(V+E)$ Code
Here is the clean, optimal way to write this:

```cpp
class Solution {
    // Helper DFS to find the candidate
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, int& candidate) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited, candidate);
            }
        }
        // As the recursive calls return, this will continually update.
        // The very last node to finish will be our final candidate.
        candidate = u; 
    }

public:
    int findMotherVertex(int V, vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
        }

        vector<bool> visited(V, false);
        int candidate = -1;

        // Step 1: Do DFS to find the ONLY potential mother vertex candidate
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, candidate);
            }
        }

        // Step 2: We have a candidate, but we must verify it. 
        // A disconnected graph might yield a fake candidate.
        fill(visited.begin(), visited.end(), false); // Reset visited array
        int count = 0;
        
        queue<int> q;
        q.push(candidate);
        visited[candidate] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            count++;
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        // If the candidate can reach all V nodes, it's our Mother Vertex.
        return (count == V) ? candidate : -1;
    }
};

```
### 💡 Why this is bulletproof:
1. **No Wasted Effort:** We only run a full graph traversal (DFS/BFS) exactly **twice**. Once to find the candidate, 
    and once to verify it.
2. **Memory Efficient:** Instead of pushing elements onto a stack like a standard Topological Sort, we just overwrite 
    a single `candidate` integer, saving memory overhead.
3. **Strictly Linear:** The time complexity is exactly $O(V+E)$, and the space complexity is $O(V+E)$ for the 
    adjacency list.
*/