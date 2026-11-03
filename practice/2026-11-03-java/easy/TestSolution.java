import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    private static int checks = 0;

    private static void eq(long[] actual, long[] expected) {
        if (!Arrays.equals(actual, expected)) {
            throw new AssertionError("expected " + Arrays.toString(expected)
                    + ", got " + Arrays.toString(actual));
        }
        checks++;
    }

    private static long[] brute(int n, int[][] patches) {
        long[] out = new long[n];
        for (int[] patch : patches) {
            for (int i = patch[0]; i <= patch[1]; i++) out[i] += patch[2];
        }
        return out;
    }

    private static int[][] copy(int[][] a) {
        int[][] b = new int[a.length][];
        for (int i = 0; i < a.length; i++) b[i] = a[i].clone();
        return b;
    }

    public static void main(String[] args) {
        eq(Solution.applyPatches(0, new int[][]{}), new long[]{});
        eq(Solution.applyPatches(4, new int[][]{}), new long[]{0, 0, 0, 0});
        eq(Solution.applyPatches(5, new int[][]{
                {0, 2, 4}, {1, 3, -2}, {3, 4, 7}}),
                new long[]{4, 2, 2, 5, 7});
        eq(Solution.applyPatches(1, new int[][]{
                {0, 0, -8}, {0, 0, 3}}), new long[]{-5});
        eq(Solution.applyPatches(3, new int[][]{
                {0, 2, 1_000_000_000}, {0, 2, 1_000_000_000},
                {0, 2, 1_000_000_000}}),
                new long[]{3_000_000_000L, 3_000_000_000L, 3_000_000_000L});
        eq(Solution.applyPatches(5, new int[][]{
                {4, 4, 5}, {0, 0, -3}, {1, 3, 0}}),
                new long[]{-3, 0, 0, 0, 5});

        Random rng = new Random(20261103);
        for (int trial = 0; trial < 1_600; trial++) {
            int n = rng.nextInt(28);
            int q = n == 0 ? 0 : rng.nextInt(35);
            int[][] patches = new int[q][3];
            for (int i = 0; i < q; i++) {
                int left = rng.nextInt(n);
                int right = left + rng.nextInt(n - left);
                patches[i] = new int[]{left, right, rng.nextInt(2001) - 1000};
            }
            int[][] original = copy(patches);
            eq(Solution.applyPatches(n, patches), brute(n, patches));
            if (!Arrays.deepEquals(patches, original)) {
                throw new AssertionError("input patches mutated");
            }
        }

        int n = 200_000, q = 200_000;
        int[][] patches = new int[q][3];
        for (int i = 0; i < q; i++) {
            patches[i] = new int[]{0, n - 1, 1_000_000_000};
        }
        long[] result = Solution.applyPatches(n, patches);
        if (result.length != n) throw new AssertionError("incorrect output length");
        eq(new long[]{result[0], result[n / 2], result[n - 1]},
                new long[]{200_000_000_000_000L, 200_000_000_000_000L,
                        200_000_000_000_000L});

        System.out.println("PASS easy: " + checks + " checks");
    }
}
