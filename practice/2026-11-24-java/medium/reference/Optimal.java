import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int longestQuietBlock(int[] ids, long budget) {
        Map<Integer, Integer> freq = new HashMap<>();
        long pairs = 0;
        int left = 0, best = 0;
        for (int right = 0; right < ids.length; right++) {
            int id = ids[right], old = freq.getOrDefault(id, 0);
            pairs += old;
            freq.put(id, old + 1);
            while (pairs > budget) {
                int gone = ids[left++], remaining = freq.get(gone) - 1;
                pairs -= remaining;
                if (remaining == 0) freq.remove(gone);
                else freq.put(gone, remaining);
            }
            best = Math.max(best, right - left + 1);
        }
        return best;
    }
}
