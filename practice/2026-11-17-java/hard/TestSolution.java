import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    private static int[][] deepCopy(int[][] source) {
        int[][] copy = new int[source.length][];
        for (int i = 0; i < source.length; i++) copy[i] = source[i].clone();
        return copy;
    }

    // Independent per-query minimax Dijkstra oracle; never constructs an MST.
    @SuppressWarnings("unchecked")
    private static int[] oracle(int n, int[][] edges, int[][] queries) {
        List<int[]>[] graph = (List<int[]>[]) new List[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();
        for (int[] e : edges) {
            graph[e[0]].add(new int[]{e[1], e[2]});
            graph[e[1]].add(new int[]{e[0], e[2]});
        }
        int[] answers = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int start = queries[i][0], target = queries[i][1];
            int[] dist = new int[n];
            Arrays.fill(dist, Integer.MAX_VALUE);
            dist[start] = 0;
            PriorityQueue<int[]> pq = new PriorityQueue<>(
                    Comparator.comparingInt(a -> a[1]));
            pq.add(new int[]{start, 0});
            while (!pq.isEmpty()) {
                int[] cur = pq.poll();
                int u = cur[0], cost = cur[1];
                if (cost != dist[u]) continue;
                for (int[] edge : graph[u]) {
                    int next = edge[0];
                    int candidate = Math.max(cost, edge[1]);
                    if (candidate < dist[next]) {
                        dist[next] = candidate;
                        pq.add(new int[]{next, candidate});
                    }
                }
            }
            answers[i] = dist[target] == Integer.MAX_VALUE ? -1 : dist[target];
        }
        return answers;
    }

    private static void check(int n, int[][] edges, int[][] queries, int[] expected) {
        int[][] edgesCopy = deepCopy(edges), queryCopy = deepCopy(queries);
        int[] got = Solution.minimumBottleneckCosts(n, edges, queries);
        if (!Arrays.equals(got, expected)) {
            throw new AssertionError("n=" + n
                    + " edges=" + Arrays.deepToString(edges)
                    + " queries=" + Arrays.deepToString(queries)
                    + " expected=" + Arrays.toString(expected)
                    + " actual=" + Arrays.toString(got));
        }
        if (!Arrays.deepEquals(edges, edgesCopy) || !Arrays.deepEquals(queries, queryCopy)) {
            throw new AssertionError("mutated input");
        }
        checks++;
    }

    public static void main(String[] args) {
        check(1, new int[][]{}, new int[][]{{0, 0}}, new int[]{0});
        check(4, new int[][]{}, new int[][]{{0, 1},{3, 3},{2, 3}},
                new int[]{-1, 0, -1});
        check(5, new int[][]{
                    {0, 1, 9}, {1, 2, 5}, {0, 2, 8},
                    {2, 3, 2}, {3, 4, 10}, {1, 4, 1}},
                new int[][]{{0,2},{0,4},{3,4},{0,0},{0,3}},
                new int[]{8, 8, 5, 0, 8});
        check(4, new int[][]{{0,1,0},{0,1,100},{1,2,7},{2,2,0}},
                new int[][]{{0,2},{0,3},{3,3},{0,1},{2,0}},
                new int[]{7,-1,0,0,7});
        check(2, new int[][]{{0,1,500_000_000},{0,1,1}},
                new int[][]{{0,1},{1,0},{0,0}},
                new int[]{1,1,0});
        check(3, new int[][]{{0,1,4},{1,2,4},{0,2,4}},
                new int[][]{{0,2},{1,2},{2,2}}, new int[]{4,4,0});

        Random rng = new Random(20261119L);
        for (int trial = 0; trial < 1_000; trial++) {
            int n = 1 + rng.nextInt(12);
            int m = rng.nextInt(38);
            int q = 1 + rng.nextInt(17);
            int[][] edges = new int[m][3];
            for (int i = 0; i < m; i++) {
                edges[i] = new int[]{
                    rng.nextInt(n), rng.nextInt(n), rng.nextInt(24)
                };
            }
            int[][] queries = new int[q][2];
            for (int i = 0; i < q; i++) {
                queries[i] = new int[]{rng.nextInt(n), rng.nextInt(n)};
            }
            check(n, edges, queries, oracle(n, edges, queries));
        }

        // Large tree with a dominated shortcut. Path [a,b] has max edge max(a,b).
        int n = 100_000;
        int[][] edges = new int[n][3];
        for (int i = 0; i < n - 1; i++) edges[i] = new int[]{i, i+1, i+1};
        edges[n-1] = new int[]{0, n-1, 1_000_000_000};
        int q = 200_000;
        int[][] queries = new int[q][2];
        int[] expected = new int[q];
        for (int i = 0; i < q; i++) {
            int a = (i * 37) % n;
            int b = (i * 113 + 37) % n;
            queries[i] = new int[]{a, b};
            expected[i] = a == b ? 0 : Math.max(a, b);
        }
        check(n, edges, queries, expected);
        System.out.println("PASS hard: " + checks + " checks");
    }
}

