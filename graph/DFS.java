import java.util.ArrayList;

public class DFS {
    void dfsRec(ArrayList<ArrayList<Integer>> adj, boolean[] visited, int s) {
        visited[s] = true;
        System.out.print(s + " ");
        for (int v : adj.get(s)) {
            if (!visited[v]) {
                dfsRec(adj, visited, v);
            }
        }
    }
    void dfs(ArrayList<ArrayList<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsRec(adj, visited, i);
            }
        }
    }
    public static void main(String[] args) {

    }
}
