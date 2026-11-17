import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    // Intentionally quadratic prefix-scan oracle: no queue.
    private static int[] oracle(int[] a) {
        int[] out = new int[a.length];
        Map<Integer, Integer> counts = new HashMap<>();
        for (int i = 0; i < a.length; i++) {
            counts.put(a[i], counts.getOrDefault(a[i], 0) + 1);
            int answer = -1;
            for (int j = 0; j <= i; j++) {
                if (counts.get(a[j]) == 1) {
                    answer = a[j];
                    break;
                }
            }
            out[i] = answer;
        }
        return out;
    }

    private static void check(int[] events, int[] expected) {
        int[] snapshot = events.clone();
        int[] actual = Solution.earliestUniqueAfterEach(events);
        if (!Arrays.equals(expected, actual)) {
            throw new AssertionError("input=" + Arrays.toString(events)
                    + " expected=" + Arrays.toString(expected)
                    + " actual=" + Arrays.toString(actual));
        }
        if (!Arrays.equals(events, snapshot)) throw new AssertionError("input was mutated");
        checks++;
    }

    public static void main(String[] args) {
        check(new int[]{}, new int[]{});
        check(new int[]{0}, new int[]{0});
        check(new int[]{7, 9, 7, 3, 9, 3}, new int[]{7, 7, 9, 9, 3, -1});
        check(new int[]{4, 4, 4, 4}, new int[]{4, -1, -1, -1});
        check(new int[]{0, 1, 0, 1, 2, 2, 3},
                new int[]{0, 0, 1, -1, 2, -1, 3});
        check(new int[]{1_000_000_000, 0, 1_000_000_000},
                new int[]{1_000_000_000, 1_000_000_000, 0});

        Random rng = new Random(20261117L);
        for (int t = 0; t < 2_000; t++) {
            int n = rng.nextInt(55);
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = rng.nextInt(13);
            check(a, oracle(a));
        }

        int[] stress = new int[180_000];
        for (int i = 0; i < stress.length; i++) stress[i] = i % 70_000;
        int[] actual = Solution.earliestUniqueAfterEach(stress);
        if (actual.length != stress.length) throw new AssertionError("stress length");
        for (int i = 0; i < actual.length; i++) {
            int expected = i < 70_000 ? 0
                    : (i < 139_999 ? i - 70_000 + 1 : -1);
            if (actual[i] != expected) {
                throw new AssertionError("stress mismatch at " + i
                        + ": got " + actual[i] + ", expected " + expected);
            }
        }
        checks++;
        System.out.println("PASS easy: " + checks + " checks");
    }
}

