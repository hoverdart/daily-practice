import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int[] longestLimitedRepeatWindow(int[] events, int k) {
        if (events.length == 0) return new int[]{-1, -1};

        Map<Integer, Integer> count = new HashMap<>();
        int left = 0;
        int repeatedTypes = 0;
        int bestLeft = 0, bestRight = 0, bestLen = 0;

        for (int right = 0; right < events.length; right++) {
            int id = events[right];
            int previous = count.getOrDefault(id, 0);
            if (previous == 1) repeatedTypes++;
            count.put(id, previous + 1);

            while (repeatedTypes > k) {
                int leaving = events[left++];
                int oldCount = count.get(leaving);
                if (oldCount == 2) repeatedTypes--;
                if (oldCount == 1) count.remove(leaving);
                else count.put(leaving, oldCount - 1);
            }

            int len = right - left + 1;
            if (len > bestLen || (len == bestLen && left < bestLeft)) {
                bestLen = len;
                bestLeft = left;
                bestRight = right;
            }
        }
        return new int[]{bestLeft, bestRight};
    }
}
