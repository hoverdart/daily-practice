import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    // Quadratic independent oracle: enumerate every left/right pair.
    private static int[] oracle(int[] a, int cap, int required) {
        int[] best = {-1, -1};
        int bestLength = 0;
        for (int left = 0; left < a.length; left++) {
            Map<Integer, Integer> counts = new HashMap<>();
            for (int right = left; right < a.length; right++) {
                int now = counts.getOrDefault(a[right], 0) + 1;
                counts.put(a[right], now);
                if (now > cap) break; // More extensions cannot repair a frequency cap.
                int length = right - left + 1;
                if (counts.size() >= required
                        && (length > bestLength
                            || (length == bestLength
                                && (best[0] == -1 || left < best[0])))) {
                    best = new int[]{left, right};
                    bestLength = length;
                }
            }
        }
        return best;
    }

    private static void check(int[] a, int cap, int required, int[] expected) {
        int[] snapshot = a.clone();
        int[] got = Solution.longestFairSession(a, cap, required);
        if (!Arrays.equals(got, expected)) {
            throw new AssertionError("a=" + Arrays.toString(a) + " cap=" + cap
                    + " required=" + required + " expected=" + Arrays.toString(expected)
                    + " got=" + Arrays.toString(got));
        }
        if (!Arrays.equals(a, snapshot)) throw new AssertionError("mutated input");
        checks++;
    }

    public static void main(String[] args) {
        check(new int[]{}, 2, 0, new int[]{-1, -1});
        check(new int[]{4, 7, 4, 9, 7, 4, 8}, 2, 3, new int[]{1, 6});
        check(new int[]{1, 1, 1, 1}, 2, 1, new int[]{0, 1});
        check(new int[]{1, 1, 1}, 1, 2, new int[]{-1, -1});
        check(new int[]{-2, -3, -2, -3, -4}, 2, 3, new int[]{0, 4});
        check(new int[]{10, 20, 10, 20, 10}, 1, 2, new int[]{0, 1});
        check(new int[]{5, 5, 5}, 200_000, 0, new int[]{0, 2});
        check(new int[]{1, 2, 3, 1, 2, 3}, 1, 3, new int[]{0, 2});
        check(new int[]{1, 2, 3}, 2, 4, new int[]{-1, -1});

        Random rng = new Random(20261118L);
        for (int trial = 0; trial < 2_100; trial++) {
            int n = rng.nextInt(48);
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = rng.nextInt(13) - 6;
            int cap = 1 + rng.nextInt(7);
            int required = rng.nextInt(16);
            check(a, cap, required, oracle(a, cap, required));
        }

        int n = 200_000;
        int[] stress = new int[n];
        for (int i = 0; i < n; i++) stress[i] = i % 1000;
        check(stress, 2, 700, new int[]{0, 1999});
        check(stress, 2, 1001, new int[]{-1, -1});
        System.out.println("PASS medium: " + checks + " checks");
    }
}

