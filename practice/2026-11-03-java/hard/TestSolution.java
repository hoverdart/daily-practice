import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    private static void eq(int[] actual, int[] expected) {
        if (!Arrays.equals(actual, expected)) {
            throw new AssertionError("expected " + Arrays.toString(expected)
                    + ", got " + Arrays.toString(actual));
        }
        checks++;
    }

    // Independent oracle: all-pairs reachability, then equivalence of
    // mutual reachability, then indegrees in the contracted DAG.
    private static int[] brute(int n, int[][] links) {
        boolean[][] reachable = new boolean[n][n];
        for (int i = 0; i < n; i++) reachable[i][i] = true;
        for (int[] e : links) reachable[e[0]][e[1]] = true;
        for (int mid = 0; mid < n; mid++) {
            for (int u = 0; u < n; u++) {
                if (!reachable[u][mid]) continue;
                for (int v = 0; v < n; v++) {
                    if (reachable[mid][v]) reachable[u][v] = true;
                }
            }
        }

        int[] group = new int[n];
        Arrays.fill(group, -1);
        List<Integer> representative = new ArrayList<>();
        for (int u = 0; u < n; u++) {
            if (group[u] != -1) continue;
            int id = representative.size();
            representative.add(u);
            for (int v = 0; v < n; v++) {
                if (reachable[u][v] && reachable[v][u]) group[v] = id;
            }
        }

        boolean[] hasIncoming = new boolean[representative.size()];
        for (int[] e : links) {
            if (group[e[0]] != group[e[1]]) hasIncoming[group[e[1]]] = true;
        }
        List<Integer> chosen = new ArrayList<>();
        for (int id = 0; id < representative.size(); id++) {
            if (!hasIncoming[id]) chosen.add(representative.get(id));
        }
        int[] out = new int[chosen.size()];
        for (int i = 0; i < out.length; i++) out[i] = chosen.get(i);
        return out;
    }

    private static int[][] copy(int[][] a) {
        int[][] b = new int[a.length][];
        for (int i = 0; i < a.length; i++) b[i] = a[i].clone();
        return b;
    }

    public static void main(String[] args) {
        eq(Solution.minimumBootStations(0, new int[][]{}), new int[]{});
        eq(Solution.minimumBootStations(1, new int[][]{}), new int[]{0});
        eq(Solution.minimumBootStations(4, new int[][]{}), new int[]{0, 1, 2, 3});
        eq(Solution.minimumBootStations(4,
                new int[][]{{0,1},{1,2},{2,3}}), new int[]{0});
        eq(Solution.minimumBootStations(4,
                new int[][]{{1,0},{2,1},{3,2}}), new int[]{3});
        eq(Solution.minimumBootStations(4,
                new int[][]{{0,1},{1,2},{2,3},{3,0}}), new int[]{0});
        eq(Solution.minimumBootStations(5,
                new int[][]{{0,1},{1,0},{2,3},{3,2},{1,2},{4,3}}),
                new int[]{0,4});
        eq(Solution.minimumBootStations(6,
                new int[][]{{0,1},{1,0},{2,3},{3,2},{1,4},{3,4},{4,5}}),
                new int[]{0,2});
        eq(Solution.minimumBootStations(4,
                new int[][]{{0,0},{0,1},{0,1},{2,2},{3,2}}),
                new int[]{0,3});

        Random rng = new Random(202611032);
        for (int trial = 0; trial < 1_800; trial++) {
            int n = rng.nextInt(10);
            int m = n == 0 ? 0 : rng.nextInt(45);
            int[][] links = new int[m][2];
            for (int j = 0; j < m; j++) {
                links[j] = new int[]{rng.nextInt(n), rng.nextInt(n)};
            }
            int[][] original = copy(links);
            eq(Solution.minimumBootStations(n, links), brute(n, links));
            if (!Arrays.deepEquals(links, original)) {
                throw new AssertionError("input links mutated");
            }
        }

        // Large chains/cycles ensure solutions do not rely on recursive DFS.
        int n = 120_000;
        int[][] chain = new int[n - 1][2];
        for (int i = 0; i < n - 1; i++) chain[i] = new int[]{i, i + 1};
        eq(Solution.minimumBootStations(n, chain), new int[]{0});
        for (int[] edge : chain) {
            int tmp = edge[0];
            edge[0] = edge[1];
            edge[1] = tmp;
        }
        eq(Solution.minimumBootStations(n, chain), new int[]{n - 1});

        int[][] cycle = new int[n][2];
        for (int i = 0; i < n; i++) cycle[i] = new int[]{i, (i + 1) % n};
        eq(Solution.minimumBootStations(n, cycle), new int[]{0});

        int pairs = 20_000;
        int[][] disconnectedPairs = new int[2 * pairs][2];
        int[] expected = new int[pairs];
        for (int p = 0; p < pairs; p++) {
            disconnectedPairs[2 * p] = new int[]{2 * p, 2 * p + 1};
            disconnectedPairs[2 * p + 1] = new int[]{2 * p + 1, 2 * p};
            expected[p] = 2 * p;
        }
        eq(Solution.minimumBootStations(2 * pairs, disconnectedPairs), expected);

        System.out.println("PASS hard: " + checks + " checks");
    }
}
