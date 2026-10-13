import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int[] shortestQuotaWindow(int[] events, int[] requiredIds, int[] minimumCounts) {
        Map<Integer, Integer> need = new HashMap<>();
        long missing = 0;
        for (int i = 0; i < requiredIds.length; i++) {
            need.put(requiredIds[i], minimumCounts[i]);
            missing += minimumCounts[i];
        }
        Map<Integer, Integer> have = new HashMap<>();
        int left = 0, bestLeft = -1, bestRight = -1;
        for (int right = 0; right < events.length; right++) {
            int value = events[right];
            if (need.containsKey(value)) {
                int count = have.getOrDefault(value, 0) + 1;
                have.put(value, count);
                if (count <= need.get(value)) missing--;
            }
            while (missing == 0) {
                if (bestLeft == -1 || right - left < bestRight - bestLeft) {
                    bestLeft = left;
                    bestRight = right;
                }
                int leaving = events[left++];
                if (need.containsKey(leaving)) {
                    int count = have.get(leaving);
                    if (count <= need.get(leaving)) missing++;
                    if (count == 1) have.remove(leaving);
                    else have.put(leaving, count - 1);
                }
            }
        }
        return new int[]{bestLeft, bestRight};
    }
}
