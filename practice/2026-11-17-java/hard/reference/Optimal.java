import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution {
    private static int find(int[] parent, int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    private static boolean union(int[] parent, int[] size, int a, int b) {
        int ra = find(parent, a);
        int rb = find(parent, b);
        if (ra == rb) return false;
        if (size[ra] < size[rb]) {
            int tmp = ra;
            ra = rb;
            rb = tmp;
        }
        parent[rb] = ra;
        size[ra] += size[rb];
        return true;
    }

    @SuppressWarnings("unchecked")
    public static int[] minimumBottleneckCosts(int n, int[][] edges, int[][] queries) {
        // Sort a shallow clone: ordering row references leaves caller's input untouched.
        int[][] sorted = edges.clone();
        Arrays.sort(sorted, (a, b) -> Integer.compare(a[2], b[2]));

        int[] dsuParent = new int[n];
        int[] dsuSize = new int[n];
        for (int i = 0; i < n; i++) {
            dsuParent[i] = i;
            dsuSize[i] = 1;
        }

        List<int[]>[] forest = (List<int[]>[]) new List[n];
        for (int i = 0; i < n; i++) forest[i] = new ArrayList<>();
        for (int[] edge : sorted) {
            int a = edge[0], b = edge[1], w = edge[2];
            if (union(dsuParent, dsuSize, a, b)) {
                forest[a].add(new int[]{b, w});
                forest[b].add(new int[]{a, w});
            }
        }

        int log = 1;
        while ((1L << log) <= n) log++;
        int[][] up = new int[log][n];
        int[][] maxOnJump = new int[log][n];
        int[] component = new int[n];
        int[] depth = new int[n];
        boolean[] seen = new boolean[n];

        // Iterative BFS over every tree, including isolated vertices.
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        for (int start = 0; start < n; start++) {
            if (seen[start]) continue;
            seen[start] = true;
            component[start] = start;
            up[0][start] = start;
            queue.addLast(start);

            while (!queue.isEmpty()) {
                int node = queue.removeFirst();
                for (int[] link : forest[node]) {
                    int next = link[0], weight = link[1];
                    if (seen[next]) continue;
                    seen[next] = true;
                    component[next] = start;
                    depth[next] = depth[node] + 1;
                    up[0][next] = node;
                    maxOnJump[0][next] = weight;
                    queue.addLast(next);
                }
            }
        }

        for (int k = 1; k < log; k++) {
            for (int node = 0; node < n; node++) {
                int midpoint = up[k - 1][node];
                up[k][node] = up[k - 1][midpoint];
                maxOnJump[k][node] = Math.max(
                        maxOnJump[k - 1][node],
                        maxOnJump[k - 1][midpoint]);
            }
        }

        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int a = queries[i][0], b = queries[i][1];
            if (a == b) {
                answer[i] = 0;
                continue;
            }
            if (component[a] != component[b]) {
                answer[i] = -1;
                continue;
            }

            int worst = 0;
            if (depth[a] < depth[b]) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            int gap = depth[a] - depth[b];
            for (int k = 0; k < log; k++) {
                if (((gap >>> k) & 1) != 0) {
                    worst = Math.max(worst, maxOnJump[k][a]);
                    a = up[k][a];
                }
            }

            if (a != b) {
                for (int k = log - 1; k >= 0; k--) {
                    if (up[k][a] != up[k][b]) {
                        worst = Math.max(worst, maxOnJump[k][a]);
                        worst = Math.max(worst, maxOnJump[k][b]);
                        a = up[k][a];
                        b = up[k][b];
                    }
                }
                // a and b are now children of their lowest common ancestor.
                worst = Math.max(worst, maxOnJump[0][a]);
                worst = Math.max(worst, maxOnJump[0][b]);
            }
            answer[i] = worst;
        }
        return answer;
    }
}

