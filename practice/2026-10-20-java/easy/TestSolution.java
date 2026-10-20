import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    private static void check(int[] got, int[] expected) {
        if (!Arrays.equals(got, expected)) {
            throw new AssertionError("Expected " + Arrays.toString(expected)
                + ", got " + Arrays.toString(got));
        }
        checks++;
    }

    private static int[] oracle(int[] a) {
        int[] ans = new int[a.length];
        for (int i = 0; i < a.length; i++) {
            for (int j = i + 1; j < a.length; j++) {
                if (a[j] > a[i]) {
                    ans[i] = j - i;
                    break;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        check(Solution.secondsUntilHigher(new int[]{}), new int[]{});
        check(Solution.secondsUntilHigher(new int[]{7}), new int[]{0});
        check(Solution.secondsUntilHigher(new int[]{3,1,4,4,5}), new int[]{2,1,2,1,0});
        check(Solution.secondsUntilHigher(new int[]{5,5,5}), new int[]{0,0,0});
        check(Solution.secondsUntilHigher(new int[]{9,7,5}), new int[]{0,0,0});
        check(Solution.secondsUntilHigher(new int[]{-2,-3,-1}), new int[]{2,1,0});
        check(Solution.secondsUntilHigher(new int[]{Integer.MIN_VALUE, Integer.MAX_VALUE}),
            new int[]{1,0});

        Random random = new Random(20261020);
        for (int t = 0; t < 700; t++) {
            int n = random.nextInt(38);
            int[] a = new int[n];
            for (int i = 0; i < n; i++) a[i] = random.nextInt(19) - 9;
            int[] copy = a.clone();
            check(Solution.secondsUntilHigher(a), oracle(a));
            check(a, copy); // must not mutate the input
        }

        int n = 100_000;
        int[] increasing = new int[n], expected = new int[n];
        for (int i = 0; i < n; i++) {
            increasing[i] = i;
            expected[i] = i + 1 == n ? 0 : 1;
        }
        check(Solution.secondsUntilHigher(increasing), expected);

        int[] decreasing = new int[n];
        for (int i = 0; i < n; i++) decreasing[i] = n - i;
        check(Solution.secondsUntilHigher(decreasing), new int[n]);

        System.out.println("PASS easy: " + checks + " checks");
    }
}
