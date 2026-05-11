import java.util.*;

public class BFS {
    void bfs(ArrayList<ArrayList<Integer>> adj, int V, int s) {
        boolean[] visited = new boolean[V];
        Queue<Integer> q = new LinkedList<Integer>();
        visited[s] = true;
        q.add(s);
        while(!q.isEmpty()) {
            int u = q.poll();
            System.out.print(u + " ");
            for (int v : adj.get(u)) {
                if(visited[v] == false) {
                    visited[v] = true;
                    q.add(v);
                }
            }
        }
    }
}
