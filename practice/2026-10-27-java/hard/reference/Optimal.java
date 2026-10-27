import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class Solution {
    public static long earliestArrival(int n, int[][] links, int source, int target) {
        List<List<int[]>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] link : links) graph.get(link[0]).add(link);

        long[] best = new long[n];
        Arrays.fill(best, Long.MAX_VALUE);
        best[source] = 0L;

        PriorityQueue<long[]> pq = new PriorityQueue<>(
                (a, b) -> Long.compare(a[0], b[0]));
        pq.offer(new long[]{0L, source});

        while (!pq.isEmpty()) {
            long[] entry = pq.poll();
            long time = entry[0];
            int u = (int) entry[1];
            if (time != best[u]) continue;
            if (u == target) return time;

            for (int[] link : graph.get(u)) {
                int v = link[1];
                long travel = link[2], period = link[3], offset = link[4];

                long depart;
                if (time <= offset) {
                    depart = offset;
                } else {
                    long remainder = (time - offset) % period;
                    depart = remainder == 0 ? time : time + (period - remainder);
                }
                long arrival = depart + travel;
                if (arrival < best[v]) {
                    best[v] = arrival;
                    pq.offer(new long[]{arrival, v});
                }
            }
        }
        return -1L;
    }
}
