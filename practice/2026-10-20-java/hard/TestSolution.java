import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class TestSolution {
    private static final long MOD = 1_000_000_007L;
    private static final long INF = Long.MAX_VALUE / 4;
    private static int checks = 0;

    private static void check(long[] got, long[] expected) {
        if (!Arrays.equals(got, expected)) {
            throw new AssertionError("Expected " + Arrays.toString(expected)
                + ", got " + Arrays.toString(got));
        }
        checks++;
    }

    // Independent oracle: Bellman-Ford distances, then dynamic programming
    // over vertices sorted by distance. Strictly positive weights make the
    // shortest-edge subgraph acyclic in this ordering.
    private static long[] oracle(int n, int[][] edges) {
        long[] dist = new long[n];
        Arrays.fill(dist, INF);
        dist[0] = 0;
        for (int pass = 0; pass < n - 1; pass++) {
            boolean changed = false;
            for (int[] e : edges) {
                if (dist[e[0]] == INF) continue;
                long candidate = dist[e[0]] + e[2];
                if (candidate < dist[e[1]]) {
                    dist[e[1]] = candidate;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        if (dist[n - 1] == INF) return new long[]{-1, 0};

        Integer[] order = new Integer[n];
        for (int i = 0; i < n; i++) order[i] = i;
        Arrays.sort(order, (a, b) -> Long.compare(dist[a], dist[b]));

        long[] ways = new long[n];
        ways[0] = 1;
        for (int u : order) {
            if (dist[u] == INF) break;
            for (int[] e : edges) {
                if (e[0] == u && dist[u] + e[2] == dist[e[1]]) {
                    ways[e[1]] = (ways[e[1]] + ways[u]) % MOD;
                }
            }
        }
        return new long[]{dist[n - 1], ways[n - 1]};
    }

    public static void main(String[] args) {
        check(Solution.fastestRouteAndCount(1, new int[][]{}), new long[]{0,1});
        check(Solution.fastestRouteAndCount(1, new int[][]{{0,0,1}}),
            new long[]{0,1});
        check(Solution.fastestRouteAndCount(4, new int[][]{
            {0,1,1},{0,2,1},{1,3,1},{2,3,1}
        }), new long[]{2,2});
        check(Solution.fastestRouteAndCount(3, new int[][]{
            {0,1,1},{0,1,1},{1,2,1}
        }), new long[]{2,2});
        check(Solution.fastestRouteAndCount(3, new int[][]{{0,1,5}}),
            new long[]{-1,0});
        check(Solution.fastestRouteAndCount(3, new int[][]{
            {0,1,2},{1,2,3},{0,2,10}
        }), new long[]{5,1});
        check(Solution.fastestRouteAndCount(4, new int[][]{
            {0,1,1_000_000_000},{1,2,1_000_000_000},
            {2,3,1_000_000_000}
        }), new long[]{3_000_000_000L,1});
        check(Solution.fastestRouteAndCount(4, new int[][]{
            {0,1,2},{1,2,2},{2,1,3},{2,3,1},{0,3,10}
        }), new long[]{5,1});

        Random rng = new Random(320261020);
        for (int t = 0; t < 650; t++) {
            int n = 1 + rng.nextInt(8);
            int m = rng.nextInt(24);
            int[][] edges = new int[m][3];
            for (int i = 0; i < m; i++) {
                edges[i] = new int[]{rng.nextInt(n), rng.nextInt(n),
                    1 + rng.nextInt(12)};
            }
            int[][] copy = new int[m][];
            for (int i = 0; i < m; i++) copy[i] = edges[i].clone();
            check(Solution.fastestRouteAndCount(n, edges), oracle(n, edges));
            for (int i = 0; i < m; i++) {
                if (!Arrays.equals(edges[i], copy[i]))
                    throw new AssertionError("Input edge mutated at " + i);
            }
        }

        // Large linear graph: detects quadratic solutions and int overflow.
        int n = 100_000;
        int[][] line = new int[n - 1][3];
        for (int i = 0; i < n - 1; i++)
            line[i] = new int[]{i, i + 1, 1_000_000_000};
        check(Solution.fastestRouteAndCount(n, line),
            new long[]{99_999_000_000_000L,1});

        // Repeated diamonds: 2^layers shortest routes, modulo MOD.
        int layers = 60;
        List<int[]> diamond = new ArrayList<>();
        int prev = 0;
        long expectedWays = 1;
        for (int i = 0; i < layers; i++) {
            int a = 3 * i + 1, b = a + 1, next = a + 2;
            diamond.add(new int[]{prev,a,1});
            diamond.add(new int[]{prev,b,1});
            diamond.add(new int[]{a,next,1});
            diamond.add(new int[]{b,next,1});
            prev = next;
            expectedWays = (expectedWays * 2) % MOD;
        }
        check(Solution.fastestRouteAndCount(3 * layers + 1,
            diamond.toArray(new int[0][])),
            new long[]{2L * layers, expectedWays});

        System.out.println("PASS hard: " + checks + " checks");
    }
}
