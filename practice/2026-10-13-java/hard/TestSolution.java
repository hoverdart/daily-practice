import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class TestSolution {
    private static int checked = 0;
    private static void check(long got, long expected) {
        if (got != expected) throw new AssertionError("Expected " + expected + " got " + got);
        checked++;
    }
    private static long oracle(int n, int[][] existing, int[][] candidates) {
        long best = Long.MAX_VALUE;
        int m = candidates.length;
        for (int mask = 0; mask < (1 << m); mask++) {
            List<List<Integer>> adj = new ArrayList<>();
            for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
            for (int[] edge : existing) { adj.get(edge[0]).add(edge[1]); adj.get(edge[1]).add(edge[0]); }
            long cost = 0;
            for (int i = 0; i < m; i++) if ((mask & (1 << i)) != 0) {
                int[] edge = candidates[i];
                adj.get(edge[0]).add(edge[1]); adj.get(edge[1]).add(edge[0]);
                cost += edge[2];
            }
            if (cost >= best) continue;
            boolean[] seen = new boolean[n];
            ArrayDeque<Integer> q = new ArrayDeque<>();
            seen[0] = true; q.add(0); int visited = 1;
            while (!q.isEmpty()) for (int v : adj.get(q.remove())) if (!seen[v]) {
                seen[v] = true; visited++; q.add(v);
            }
            if (visited == n) best = cost;
        }
        return best == Long.MAX_VALUE ? -1 : best;
    }
    public static void main(String[] args) {
        check(Solution.minimumUpgradeCost(1, new int[][]{}, new int[][]{}), 0);
        check(Solution.minimumUpgradeCost(3, new int[][]{{0,1}}, new int[][]{{1,2,7},{0,2,9}}), 7);
        check(Solution.minimumUpgradeCost(4, new int[][]{{0,1},{1,0},{2,3}}, new int[][]{{1,2,5},{0,3,2}}), 2);
        check(Solution.minimumUpgradeCost(3, new int[][]{}, new int[][]{{0,1,1}}), -1);
        check(Solution.minimumUpgradeCost(3, new int[][]{}, new int[][]{{0,1,4},{0,1,1},{1,2,3},{2,2,0}}), 4);
        Random rng = new Random(81013);
        for (int t = 0; t < 250; t++) {
            int n = 1 + rng.nextInt(7), m = rng.nextInt(11), e = rng.nextInt(6);
            int[][] existing = new int[e][2], candidates = new int[m][3];
            for (int i = 0; i < e; i++) { existing[i][0] = rng.nextInt(n); existing[i][1] = rng.nextInt(n); }
            for (int i = 0; i < m; i++) {
                candidates[i][0] = rng.nextInt(n);
                candidates[i][1] = rng.nextInt(n);
                candidates[i][2] = rng.nextInt(15);
            }
            check(Solution.minimumUpgradeCost(n, existing, candidates), oracle(n, existing, candidates));
        }
        int n = 30000;
        int[][] candidates = new int[2 * (n - 1)][3];
        for (int i = 0; i < n - 1; i++) {
            candidates[i] = new int[]{i,i+1,1};
            candidates[n - 1 + i] = new int[]{i,i+1,100};
        }
        check(Solution.minimumUpgradeCost(n, new int[][]{}, candidates), n - 1);
        System.out.println("PASS hard: " + checked + " checks");
    }
}
