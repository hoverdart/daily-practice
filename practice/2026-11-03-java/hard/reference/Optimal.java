import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution {
    public static int[] minimumBootStations(int n, int[][] links) {
        List<List<Integer>> outgoing = new ArrayList<>(n);
        List<List<Integer>> reversed = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            outgoing.add(new ArrayList<>());
            reversed.add(new ArrayList<>());
        }
        for (int[] link : links) {
            outgoing.get(link[0]).add(link[1]);
            reversed.get(link[1]).add(link[0]);
        }

        // Kosaraju pass 1: iterative DFS *finishing order* on original graph.
        boolean[] seen = new boolean[n];
        int[] nextNeighbor = new int[n];
        int[] stack = new int[n];
        int[] finishing = new int[n];
        int finished = 0;
        for (int start = 0; start < n; start++) {
            if (seen[start]) continue;
            int depth = 0;
            seen[start] = true;
            stack[depth++] = start;
            while (depth > 0) {
                int u = stack[depth - 1];
                List<Integer> neighbors = outgoing.get(u);
                if (nextNeighbor[u] < neighbors.size()) {
                    int v = neighbors.get(nextNeighbor[u]++);
                    if (!seen[v]) {
                        seen[v] = true;
                        stack[depth++] = v;
                    }
                } else {
                    finishing[finished++] = u;
                    depth--;
                }
            }
        }

        // Pass 2: reversed edges, processing decreasing finish time.
        int[] component = new int[n];
        Arrays.fill(component, -1);
        List<Integer> minimumIds = new ArrayList<>();
        for (int i = n - 1; i >= 0; i--) {
            int start = finishing[i];
            if (component[start] != -1) continue;
            int id = minimumIds.size();
            int smallest = start;
            int size = 0;
            stack[size++] = start;
            component[start] = id;
            while (size > 0) {
                int u = stack[--size];
                smallest = Math.min(smallest, u);
                for (int v : reversed.get(u)) {
                    if (component[v] == -1) {
                        component[v] = id;
                        stack[size++] = v;
                    }
                }
            }
            minimumIds.add(smallest);
        }

        // Condensation graph is a DAG. Only source SCCs need booting.
        boolean[] hasIncoming = new boolean[minimumIds.size()];
        for (int[] link : links) {
            int from = component[link[0]], to = component[link[1]];
            if (from != to) hasIncoming[to] = true;
        }

        boolean[] selected = new boolean[n];
        int count = 0;
        for (int id = 0; id < hasIncoming.length; id++) {
            if (!hasIncoming[id]) {
                selected[minimumIds.get(id)] = true;
                count++;
            }
        }
        int[] answer = new int[count];
        int pos = 0;
        for (int station = 0; station < n; station++) {
            if (selected[station]) answer[pos++] = station;
        }
        return answer;
    }
}
