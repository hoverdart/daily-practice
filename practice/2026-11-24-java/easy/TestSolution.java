import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    static int checks;
    static int[] oracle(int[] a) {
        int[] out = new int[a.length];
        Arrays.fill(out, -1);
        for (int i = 0; i < a.length; i++)
            for (int j = i - 1; j >= 0; j--)
                if (a[j] > a[i]) { out[i] = j; break; }
        return out;
    }
    static void check(int[] a, int[] expected) {
        int[] snapshot = a.clone();
        int[] got = Solution.previousHigher(a);
        if (!Arrays.equals(got, expected) || !Arrays.equals(a, snapshot))
            throw new AssertionError("input=" + Arrays.toString(snapshot) + " expected=" + Arrays.toString(expected) + " got=" + Arrays.toString(got));
        checks++;
    }
    public static void main(String[] args) {
        check(new int[]{}, new int[]{});
        check(new int[]{5}, new int[]{-1});
        check(new int[]{8, 3, 3, 5, 2, 8}, new int[]{-1, 0, 0, 0, 3, -1});
        check(new int[]{4, 4, 4}, new int[]{-1, -1, -1});
        check(new int[]{Integer.MAX_VALUE, Integer.MIN_VALUE, -1}, new int[]{-1, 0, 0});
        Random rng = new Random(20261124L);
        for (int t = 0; t < 1500; t++) {
            int[] a = new int[rng.nextInt(65)];
            for (int i = 0; i < a.length; i++) a[i] = rng.nextInt(21) - 10;
            check(a, oracle(a));
        }
        int n = 200000;
        int[] a = new int[n], expected = new int[n];
        for (int i = 0; i < n; i++) { a[i] = n - i; expected[i] = i - 1; }
        check(a, expected);
        Arrays.fill(expected, -1);
        for (int i = 0; i < n; i++) a[i] = i;
        check(a, expected);
        System.out.println("PASS easy: " + checks + " checks");
    }
}
