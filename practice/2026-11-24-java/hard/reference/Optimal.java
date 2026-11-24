import java.util.*;

public class Solution {
    private static final class State {
        final int vertex;
        final long cost;
        State(int vertex, long cost) { this.vertex = vertex; this.cost = cost; }
    }
    public static long secondArrival(int n, int[][] links, int start, int target) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] e : links) {
            graph.get(e[0]).add(new int[]{e[1], e[2]});
            graph.get(e[1]).add(new int[]{e[0], e[2]});
        }
        long[] first = new long[n], second = new long[n];
        Arrays.fill(first, Long.MAX_VALUE);
        Arrays.fill(second, Long.MAX_VALUE);
        PriorityQueue<State> pq = new PriorityQueue<>(Comparator.comparingLong(s -> s.cost));
        first[start] = 0;
        pq.add(new State(start, 0));
        while (!pq.isEmpty()) {
            State cur = pq.remove();
            int u = cur.vertex;
            if (cur.cost != first[u] && cur.cost != second[u]) continue;
            if (u == target && cur.cost == second[u]) return cur.cost;
            for (int[] e : graph.get(u)) {
                int v = e[0];
                long candidate = cur.cost + e[1];
                if (candidate < first[v]) {
                    long old = first[v];
                    first[v] = candidate;
                    pq.add(new State(v, candidate));
                    if (old < second[v]) second[v] = old;
                    // The old first already has a heap ticket if it is finite.
                } else if (candidate > first[v] && candidate < second[v]) {
                    second[v] = candidate;
                    pq.add(new State(v, candidate));
                }
            }
        }
        return -1;
    }
}
