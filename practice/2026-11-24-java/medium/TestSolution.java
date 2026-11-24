import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    static int checks;
    static int oracle(int[] a, long k) {
        int best = 0;
        for (int l = 0; l < a.length; l++) {
            long pairs = 0;
            for (int r = l; r < a.length; r++) {
                for (int i = l; i < r; i++) if (a[i] == a[r]) pairs++;
                if (pairs <= k) best = Math.max(best, r - l + 1);
            }
        }
        return best;
    }
    static void check(int[] a, long k, int expected) {
        int[] snapshot = a.clone();
        int got = Solution.longestQuietBlock(a, k);
        if (got != expected || !Arrays.equals(a, snapshot))
            throw new AssertionError("input=" + Arrays.toString(snapshot) + " k=" + k + " expected=" + expected + " got=" + got);
        checks++;
    }
    public static void main(String[] args) {
        check(new int[]{}, 0, 0);
        check(new int[]{7}, 0, 1);
        check(new int[]{1,2,1,2,1}, 2, 4);
        check(new int[]{4,4,4,4}, 3, 3);
        check(new int[]{-1,2,-1,3,2,4}, 0, 4);
        check(new int[]{1,2,3}, Long.MAX_VALUE, 3);
        Random rng = new Random(20261125L);
        for (int t = 0; t < 1500; t++) {
            int[] a = new int[rng.nextInt(30)];
            for (int i = 0; i < a.length; i++) a[i] = rng.nextInt(8) - 4;
            long k = rng.nextInt(65);
            check(a, k, oracle(a, k));
        }
        int[] a = new int[200000];
        check(a, 4_999_950_000L, 100000);
        check(a, 19_999_900_000L, 200000);
        check(a, 0, 1);
        System.out.println("PASS medium: " + checks + " checks");
    }
}
