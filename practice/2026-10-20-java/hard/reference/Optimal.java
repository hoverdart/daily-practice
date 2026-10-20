import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class Solution {
    private static final int MOD = 1_000_000_007;

    public static long[] fastestRouteAndCount(int n, int[][] edges) {
        List<List<int[]>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] e : edges) graph.get(e[0]).add(new int[]{e[1], e[2]});

        long inf = Long.MAX_VALUE / 4;
        long[] dist = new long[n];
        Arrays.fill(dist, inf);
        int[] ways = new int[n];
        dist[0] = 0;
        ways[0] = 1;

        // Heap entries are {tentativeDistance, vertex}.
        PriorityQueue<long[]> pq = new PriorityQueue<>(
            (a, b) -> Long.compare(a[0], b[0]));
        pq.add(new long[]{0, 0});

        while (!pq.isEmpty()) {
            long[] state = pq.poll();
            long distance = state[0];
            int u = (int) state[1];
            if (distance != dist[u]) continue; // stale entry

            for (int[] edge : graph.get(u)) {
                int v = edge[0];
                long candidate = distance + edge[1];
                if (candidate < dist[v]) {
                    dist[v] = candidate;
                    ways[v] = ways[u];
                    pq.add(new long[]{candidate, v});
                } else if (candidate == dist[v]) {
                    ways[v] = (int) (((long) ways[v] + ways[u]) % MOD);
                }
            }
        }

        if (dist[n - 1] == inf) return new long[]{-1, 0};
        return new long[]{dist[n - 1], ways[n - 1]};
    }
}
