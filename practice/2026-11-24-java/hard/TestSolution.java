import java.util.*;

public class TestSolution {
    static int checks;
    // Independent cost-indexed reachability DP for small positive-weight graphs.
    static long oracle(int n, int[][] links, int s, int t) {
        int max = 1;
        for (int[] e : links) max = Math.max(max, e[2]);
        int cap = (n + 1) * max;
        boolean[][] reachable = new boolean[cap + 1][n];
        reachable[0][s] = true;
        int found = 0;
        for (int cost = 0; cost <= cap; cost++) {
            if (reachable[cost][t] && ++found == 2) return cost;
            for (int[] e : links) {
                int next = cost + e[2];
                if (next > cap) continue;
                if (reachable[cost][e[0]]) reachable[next][e[1]] = true;
                if (reachable[cost][e[1]]) reachable[next][e[0]] = true;
            }
        }
        return -1;
    }
    static void check(int n, int[][] edges, int s, int t, long expected) {
        int[][] snapshot = Arrays.stream(edges).map(int[]::clone).toArray(int[][]::new);
        long got = Solution.secondArrival(n, edges, s, t);
        if (got != expected || !Arrays.deepEquals(edges, snapshot))
            throw new AssertionError("n=" + n + " edges=" + Arrays.deepToString(snapshot) + " s=" + s + " t=" + t + " expected=" + expected + " got=" + got);
        checks++;
    }
    public static void main(String[] args) {
        check(1, new int[][]{}, 0, 0, -1);
        check(2, new int[][]{{0,1,5}}, 0, 1, 15);
        check(2, new int[][]{{0,1,5}}, 0, 0, 10);
        check(3, new int[][]{{0,1,1}}, 0, 2, -1);
        check(3, new int[][]{{0,1,1},{1,2,1},{0,2,2}}, 0, 2, 4);
        check(2, new int[][]{{0,1,3},{0,1,3},{0,1,4}}, 0, 1, 4);
        check(3, new int[][]{{0,1,1_000_000_000},{1,2,1_000_000_000}}, 0, 2, 4_000_000_000L);
        check(4, new int[][]{{0,1,9},{0,2,1},{2,1,1},{1,3,1}}, 0, 3, 5);
        Random rng = new Random(20261126L);
        for (int trial = 0; trial < 2000; trial++) {
            int n = 1 + rng.nextInt(8);
            int m = n == 1 ? 0 : rng.nextInt(22);
            int[][] e = new int[m][3];
            for (int i = 0; i < m; i++) {
                int u = rng.nextInt(n), v = rng.nextInt(n - 1);
                if (v >= u) v++;
                e[i] = new int[]{u, v, 1 + rng.nextInt(9)};
            }
            int s = rng.nextInt(n), t = rng.nextInt(n);
            check(n, e, s, t, oracle(n, e, s, t));
        }
        int n = 100000;
        int[][] chain = new int[n - 1][3];
        for (int i = 0; i < n - 1; i++) chain[i] = new int[]{i, i + 1, 1};
        check(n, chain, 0, n - 1, n + 1L);
        System.out.println("PASS hard: " + checks + " checks");
    }
}
