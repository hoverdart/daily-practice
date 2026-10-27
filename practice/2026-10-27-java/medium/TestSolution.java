import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class TestSolution {
    private static int checks = 0;
    private static void eq(long actual, long expected) {
        if (actual != expected) throw new AssertionError("expected " + expected + ", got " + actual);
        checks++;
    }

    private static long brute(int[] codes, int[] costs, int k, long budget) {
        long answer = 0;
        for (int left = 0; left < codes.length; left++) {
            Set<Integer> distinct = new HashSet<>();
            long sum = 0;
            for (int right = left; right < codes.length; right++) {
                distinct.add(codes[right]);
                sum += costs[right];
                if (distinct.size() == k && sum <= budget) answer++;
            }
        }
        return answer;
    }

    public static void main(String[] args) {
        eq(Solution.countWindows(new int[]{1,2,1}, new int[]{1,2,1}, 2, 3), 2);
        eq(Solution.countWindows(new int[]{7,7,7}, new int[]{0,0,0}, 1, 0), 6);
        eq(Solution.countWindows(new int[]{1,2}, new int[]{0,0}, 0, 0), 0);
        eq(Solution.countWindows(new int[]{1,2,3}, new int[]{1,1,1}, 2, 1), 0);
        eq(Solution.countWindows(new int[]{}, new int[]{}, 1, 10), 0);
        eq(Solution.countWindows(new int[]{-1,-1,2}, new int[]{2,0,3}, 1, 2), 3);
        eq(Solution.countWindows(new int[]{5,6,5}, new int[]{0,0,0}, 2, 0), 3);

        Random random = new Random(27261020);
        for (int trial = 0; trial < 1400; trial++) {
            int n = random.nextInt(20);
            int[] codes = new int[n], costs = new int[n];
            for (int i = 0; i < n; i++) {
                codes[i] = random.nextInt(9) - 4;
                costs[i] = random.nextInt(7);
            }
            int k = random.nextInt(n + 3);
            long budget = random.nextInt(35);
            int[] codeCopy = codes.clone(), costCopy = costs.clone();
            eq(Solution.countWindows(codes, costs, k, budget),
                    brute(codes, costs, k, budget));
            if (!Arrays.equals(codes, codeCopy) || !Arrays.equals(costs, costCopy)) {
                throw new AssertionError("input mutated");
            }
        }

        int n = 100_000;
        int[] same = new int[n], zero = new int[n];
        Arrays.fill(same, 17);
        eq(Solution.countWindows(same, zero, 1, 0), (long)n * (n + 1) / 2);
        eq(Solution.countWindows(same, zero, 2, 0), 0);
        int[] distinct = new int[n], ones = new int[n];
        for (int i = 0; i < n; i++) { distinct[i] = i; ones[i] = 1; }
        eq(Solution.countWindows(distinct, ones, 3, 5), n - 2L);
        eq(Solution.countWindows(distinct, ones, 3, 2), 0);
        System.out.println("PASS medium: " + checks + " checks");
    }
}
