import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class TestSolution {
    private static int checks = 0;

    private static void eq(int[] actual, int[] expected) {
        if (!Arrays.equals(actual, expected)) {
            throw new AssertionError("expected " + Arrays.toString(expected)
                    + ", got " + Arrays.toString(actual));
        }
        checks++;
    }

    private static long pairKey(int a, int b) {
        return ((long) a << 32) | (b & 0xffff_ffffL);
    }

    // Independent quadratic-window oracle using a distinct-transition set.
    private static int[] brute(int[] types, int k) {
        int bestL = 0, bestR = 0;
        for (int left = 0; left < types.length; left++) {
            Set<Long> transitions = new HashSet<>();
            for (int right = left; right < types.length; right++) {
                if (right > left && types[right - 1] != types[right]) {
                    transitions.add(pairKey(types[right - 1], types[right]));
                }
                if (transitions.size() <= k && right + 1 - left > bestR - bestL) {
                    bestL = left;
                    bestR = right + 1;
                }
            }
        }
        return new int[]{bestL, bestR};
    }

    public static void main(String[] args) {
        eq(Solution.longestHandoffWindow(new int[]{}, 0), new int[]{0, 0});
        eq(Solution.longestHandoffWindow(new int[]{7}, 0), new int[]{0, 1});
        eq(Solution.longestHandoffWindow(new int[]{4, 4, 4}, 0), new int[]{0, 3});
        eq(Solution.longestHandoffWindow(new int[]{1, 2, 1, 2}, 1),
                new int[]{0, 2});
        eq(Solution.longestHandoffWindow(new int[]{1, 2, 1, 2}, 2),
                new int[]{0, 4});
        eq(Solution.longestHandoffWindow(new int[]{1, 1, 2, 2, 1, 1, 2}, 1),
                new int[]{0, 4});
        eq(Solution.longestHandoffWindow(new int[]{1, 2, 1, 2, 1}, 2),
                new int[]{0, 5});
        eq(Solution.longestHandoffWindow(new int[]{1, 1, 2, 2, 3, 3}, 1),
                new int[]{0, 4});
        eq(Solution.longestHandoffWindow(new int[]{2, 1, 2, 1}, 0),
                new int[]{0, 1});
        eq(Solution.longestHandoffWindow(
                new int[]{Integer.MIN_VALUE, Integer.MAX_VALUE,
                        Integer.MIN_VALUE, Integer.MAX_VALUE}, 1),
                new int[]{0, 2});
        eq(Solution.longestHandoffWindow(new int[]{1, 2, 2, 3, 2, 2}, 2),
                new int[]{1, 6});

        Random rng = new Random(202611031);
        for (int trial = 0; trial < 1_700; trial++) {
            int n = rng.nextInt(18);
            int[] types = new int[n];
            for (int i = 0; i < n; i++) types[i] = rng.nextInt(9) - 4;
            int k = rng.nextInt(n + 1);
            int[] original = types.clone();
            eq(Solution.longestHandoffWindow(types, k), brute(types, k));
            if (!Arrays.equals(types, original)) {
                throw new AssertionError("input array mutated");
            }
        }

        int n = 200_000;
        int[] same = new int[n];
        Arrays.fill(same, -7);
        eq(Solution.longestHandoffWindow(same, 0), new int[]{0, n});
        int[] alternating = new int[n];
        for (int i = 0; i < n; i++) alternating[i] = i & 1;
        eq(Solution.longestHandoffWindow(alternating, 1), new int[]{0, 2});
        eq(Solution.longestHandoffWindow(alternating, 2), new int[]{0, n});
        int[] unique = new int[n];
        for (int i = 0; i < n; i++) unique[i] = i;
        eq(Solution.longestHandoffWindow(unique, 0), new int[]{0, 1});
        eq(Solution.longestHandoffWindow(unique, 1), new int[]{0, 2});
        eq(Solution.longestHandoffWindow(unique, n), new int[]{0, n});

        System.out.println("PASS medium: " + checks + " checks");
    }
}
