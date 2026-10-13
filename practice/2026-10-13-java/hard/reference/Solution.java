import java.util.Arrays;
import java.util.Comparator;

public class Solution {
    private static class DSU {
        private final int[] parent, size;
        private int components;
        DSU(int n) {
            parent = new int[n]; size = new int[n]; components = n;
            for (int i = 0; i < n; i++) { parent[i] = i; size[i] = 1; }
        }
        int find(int x) {
            while (x != parent[x]) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }
        boolean union(int a, int b) {
            int ra = find(a), rb = find(b);
            if (ra == rb) return false;
            if (size[ra] < size[rb]) { int tmp = ra; ra = rb; rb = tmp; }
            parent[rb] = ra;
            size[ra] += size[rb];
            components--;
            return true;
        }
    }
    public static long minimumUpgradeCost(int n, int[][] existing, int[][] candidates) {
        DSU dsu = new DSU(n);
        for (int[] edge : existing) dsu.union(edge[0], edge[1]);
        int[][] sorted = candidates.clone();
        Arrays.sort(sorted, Comparator.comparingInt(edge -> edge[2]));
        long cost = 0;
        for (int[] edge : sorted) {
            if (dsu.union(edge[0], edge[1])) {
                cost += edge[2];
                if (dsu.components == 1) return cost;
            }
        }
        return dsu.components == 1 ? cost : -1;
    }
}
