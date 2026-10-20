import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    private static void check(int[] actual, int[] expected) {
        if (!Arrays.equals(actual, expected)) {
            throw new AssertionError("Expected " + Arrays.toString(expected)
                + ", got " + Arrays.toString(actual));
        }
        checks++;
    }

    private static int[] oracle(int[] events, int k) {
        int bestLeft = -1, bestRight = -1, bestLen = 0;
        for (int left = 0; left < events.length; left++) {
            Map<Integer, Integer> count = new HashMap<>();
            int repeatedTypes = 0;
            for (int right = left; right < events.length; right++) {
                int previous = count.getOrDefault(events[right], 0);
                if (previous == 1) repeatedTypes++;
                count.put(events[right], previous + 1);
                int len = right - left + 1;
                if (repeatedTypes <= k && (len > bestLen
                    || (len == bestLen && (bestLeft == -1 || left < bestLeft)))) {
                    bestLen = len;
                    bestLeft = left;
                    bestRight = right;
                }
            }
        }
        return new int[]{bestLeft, bestRight};
    }

    public static void main(String[] args) {
        check(Solution.longestLimitedRepeatWindow(new int[]{}, 0), new int[]{-1,-1});
        check(Solution.longestLimitedRepeatWindow(new int[]{4,4,4,9,9,7,7}, 1),
            new int[]{0,3});
        check(Solution.longestLimitedRepeatWindow(new int[]{1,2,1,2,3}, 1),
            new int[]{1,4});
        check(Solution.longestLimitedRepeatWindow(new int[]{2,3,4}, 0),
            new int[]{0,2});
        check(Solution.longestLimitedRepeatWindow(new int[]{1,1,1,1}, 0),
            new int[]{0,0});
        check(Solution.longestLimitedRepeatWindow(new int[]{1,1,1,1}, 1),
            new int[]{0,3});
        check(Solution.longestLimitedRepeatWindow(new int[]{-1,-1,2,2,-1}, 1),
            new int[]{0,2});
        check(Solution.longestLimitedRepeatWindow(new int[]{Integer.MIN_VALUE,
            Integer.MAX_VALUE, Integer.MIN_VALUE}, 0), new int[]{0,1});

        Random rng = new Random(120261020);
        for (int t = 0; t < 650; t++) {
            int n = rng.nextInt(30);
            int[] events = new int[n];
            for (int i = 0; i < n; i++) events[i] = rng.nextInt(9) - 4;
            int k = rng.nextInt(5);
            int[] copy = events.clone();
            check(Solution.longestLimitedRepeatWindow(events, k), oracle(events, k));
            check(events, copy);
        }

        int n = 100_000;
        int[] alternating = new int[n];
        for (int i = 0; i < n; i++) alternating[i] = i % 2;
        check(Solution.longestLimitedRepeatWindow(alternating, 1), new int[]{0,2});
        check(Solution.longestLimitedRepeatWindow(alternating, 2),
            new int[]{0,n-1});
        check(Solution.longestLimitedRepeatWindow(alternating, 0), new int[]{0,1});

        System.out.println("PASS medium: " + checks + " checks");
    }
}
