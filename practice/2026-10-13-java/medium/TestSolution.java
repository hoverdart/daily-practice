import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class TestSolution {
    private static int checked = 0;
    private static void check(int[] got, int[] want) {
        if (!Arrays.equals(got, want)) throw new AssertionError("Expected " + Arrays.toString(want) + " got " + Arrays.toString(got));
        checked++;
    }
    private static int[] oracle(int[] events, int[] ids, int[] quotas) {
        int bestL = -1, bestR = -1;
        for (int l = 0; l < events.length; l++) {
            Map<Integer, Integer> freq = new HashMap<>();
            for (int r = l; r < events.length; r++) {
                freq.put(events[r], freq.getOrDefault(events[r], 0) + 1);
                boolean valid = true;
                for (int k = 0; k < ids.length; k++) {
                    if (freq.getOrDefault(ids[k], 0) < quotas[k]) { valid = false; break; }
                }
                if (valid) {
                    if (bestL < 0 || r - l < bestR - bestL) { bestL = l; bestR = r; }
                    break;
                }
            }
        }
        return new int[]{bestL, bestR};
    }
    public static void main(String[] args) {
        check(Solution.shortestQuotaWindow(new int[]{}, new int[]{2}, new int[]{1}), new int[]{-1,-1});
        check(Solution.shortestQuotaWindow(new int[]{1,2,1,3,2,1}, new int[]{1,2}, new int[]{2,1}), new int[]{0,2});
        check(Solution.shortestQuotaWindow(new int[]{8,7,8,7,8}, new int[]{7,8}, new int[]{1,1}), new int[]{0,1});
        check(Solution.shortestQuotaWindow(new int[]{-1,0,-1,2}, new int[]{-1,2}, new int[]{2,1}), new int[]{0,3});
        check(Solution.shortestQuotaWindow(new int[]{4,4,4}, new int[]{4}, new int[]{4}), new int[]{-1,-1});
        Random rng = new Random(71013);
        for (int t = 0; t < 450; t++) {
            int n = rng.nextInt(17), k = 1 + rng.nextInt(4);
            int[] events = new int[n], ids = new int[k], quotas = new int[k];
            for (int i = 0; i < n; i++) events[i] = rng.nextInt(7) - 3;
            for (int i = 0; i < k; i++) { ids[i] = i - 2; quotas[i] = 1 + rng.nextInt(3); }
            check(Solution.shortestQuotaWindow(events, ids, quotas), oracle(events, ids, quotas));
        }
        int[] large = new int[100000];
        for (int i = 0; i < large.length; i++) large[i] = i % 2 == 0 ? 4 : 7;
        check(Solution.shortestQuotaWindow(large, new int[]{4,7}, new int[]{2,2}), new int[]{0,3});
        System.out.println("PASS medium: " + checked + " checks");
    }
}
