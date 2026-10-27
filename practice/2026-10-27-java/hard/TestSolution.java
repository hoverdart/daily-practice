import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;
    private static void eq(long actual, long expected) {
        if (actual != expected) throw new AssertionError("expected " + expected + ", got " + actual);
        checks++;
    }

    // Independent oracle: time-expanded reachability with one-unit waiting.
    // In the small random cases, any reachable target has a simple path arriving
    // by time 110 (at most 6 links, each with <=4 wait and <=5 travel).
    private static long timeExpandedOracle(int n, int[][] links, int source, int target) {
        final int horizon = 110;
        boolean[][] reachable = new boolean[horizon + 1][n];
        reachable[0][source] = true;
        for (int time = 0; time <= horizon; time++) {
            if (reachable[time][target]) return time;
            for (int u = 0; u < n; u++) {
                if (!reachable[time][u]) continue;
                if (time < horizon) reachable[time + 1][u] = true;
                for (int[] edge : links) {
                    if (edge[0] != u) continue;
                    int offset = edge[4], period = edge[3];
                    if (time >= offset && (time - offset) % period == 0
                            && time + edge[2] <= horizon) {
                        reachable[time + edge[2]][edge[1]] = true;
                    }
                }
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        eq(Solution.earliestArrival(2, new int[][]{{0,1,3,5,2}}, 0, 1), 5);
        eq(Solution.earliestArrival(3, new int[][]{
                {0,1,2,4,1}, {1,2,1,5,0}, {0,2,10,1,0}}, 0, 2), 6);
        eq(Solution.earliestArrival(1, new int[][]{}, 0, 0), 0);
        eq(Solution.earliestArrival(2, new int[][]{}, 0, 1), -1);
        eq(Solution.earliestArrival(3, new int[][]{
                {0,1,2,2,0}, {1,2,2,2,1}}, 0, 2), 5);
        eq(Solution.earliestArrival(2, new int[][]{
                {0,1,5,1,0}, {0,1,1,3,2}}, 0, 1), 3);
        eq(Solution.earliestArrival(3, new int[][]{
                {0,0,1,1,0}, {1,2,1,1,0}}, 0, 2), -1);

        Random random = new Random(2026102709);
        for (int trial = 0; trial < 850; trial++) {
            int n = 1 + random.nextInt(7);
            int m = random.nextInt(n * n + 1);
            int[][] links = new int[m][5];
            for (int i = 0; i < m; i++) {
                int period = 1 + random.nextInt(5);
                links[i] = new int[]{
                        random.nextInt(n), random.nextInt(n),
                        1 + random.nextInt(5), period, random.nextInt(period)};
            }
            int source = random.nextInt(n), target = random.nextInt(n);
            int[][] original = new int[m][];
            for (int i = 0; i < m; i++) original[i] = links[i].clone();
            eq(Solution.earliestArrival(n, links, source, target),
                    timeExpandedOracle(n, links, source, target));
            for (int i = 0; i < m; i++) {
                if (!Arrays.equals(original[i], links[i])) {
                    throw new AssertionError("input mutated");
                }
            }
        }

        int n = 100_000;
        int[][] chain = new int[n - 1][5];
        for (int i = 0; i < n - 1; i++) {
            chain[i] = new int[]{i, i + 1, 1, 1, 0};
        }
        eq(Solution.earliestArrival(n, chain, 0, n - 1), n - 1L);
        eq(Solution.earliestArrival(2,
                new int[][]{{0,1,1,1_000_000,999_999}}, 0, 1), 1_000_000L);
        System.out.println("PASS hard: " + checks + " checks");
    }
}
