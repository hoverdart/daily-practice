import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;

public class TestSolution {
    private static int checks;
    private static void eq(long actual, long expected) {
        if (actual != expected) throw new AssertionError("expected " + expected + ", got " + actual);
        checks++;
    }
    // Independent O(n^2) enumeration, independent of shrinking logic.
    private static long oracle(int[] channel, int[] cost, int k, long budget) {
        long result = 0;
        for (int l = 0; l < channel.length; l++) {
            HashSet<Integer> distinct = new HashSet<>();
            long sum = 0;
            for (int r = l; r < channel.length; r++) {
                distinct.add(channel[r]);
                sum += cost[r];
                if (distinct.size() <= k && sum <= budget) result++;
            }
        }
        return result;
    }
    private static void check(int[] channel, int[] cost, int k, long budget,
                              long expected) {
        int[] a = channel.clone(), b = cost.clone();
        eq(Solution.countAffordableBursts(channel, cost, k, budget), expected);
        if (!Arrays.equals(channel, a) || !Arrays.equals(cost, b))
            throw new AssertionError("input modified");
    }
    public static void main(String[] args) {
        check(new int[]{}, new int[]{}, 0, 0L, 0);
        check(new int[]{4,4,7,4}, new int[]{2,3,1,2}, 2, 5, 7);
        check(new int[]{1,2,3}, new int[]{0,0,0}, 2, 0, 5);
        check(new int[]{1,2,3}, new int[]{0,0,0}, 0, 100, 0);
        check(new int[]{-7,-7,-7}, new int[]{3,3,3}, 1, 3, 3);
        check(new int[]{-5,Integer.MIN_VALUE, Integer.MAX_VALUE},
                new int[]{0,0,0}, 3, 0, 6);
        check(new int[]{2,2,2}, new int[]{1_000_000_000,1_000_000_000,1_000_000_000},
                1, 3_000_000_000L, 6);
        check(new int[]{1,2,1}, new int[]{2,2,2}, 1, 10, 3);
        Random rnd = new Random(20261110);
        for (int trial = 0; trial < 1_900; trial++) {
            int n = rnd.nextInt(38);
            int[] a = new int[n], b = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = rnd.nextInt(8) - 4;
                b[i] = rnd.nextInt(12);
            }
            int k = rnd.nextInt(n+2);
            long budget = rnd.nextInt(110);
            check(a, b, k, budget, oracle(a,b,k,budget));
        }
        int n = 200_000;
        int[] channels = new int[n], costs = new int[n];
        Arrays.fill(channels, -3); // zero-cost windows are all valid
        check(channels, costs, 1, 0,
                (long)n * (n+1L) / 2L);
        for (int i = 0; i < n; i++) {
            channels[i] = i % 2;
            costs[i] = 1;
        }
        check(channels, costs, 2, 1, n); // only singletons
        Arrays.fill(channels, 7);
        Arrays.fill(costs, 1_000_000_000);
        check(channels, costs, 1, 1_000_000_000_000_000L,
                (long)n * (n+1L) / 2L);
        System.out.println("PASS medium: " + checks + " checks");
    }
}
