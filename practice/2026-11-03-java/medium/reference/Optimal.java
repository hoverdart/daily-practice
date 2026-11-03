import java.util.HashMap;
import java.util.Map;

public class Solution {
    private static long transitionKey(int from, int to) {
        return ((long) from << 32) | (to & 0xffff_ffffL);
    }

    public static int[] longestHandoffWindow(int[] types, int k) {
        Map<Long, Integer> frequency = new HashMap<>();
        int left = 0, bestLeft = 0, bestRight = 0;

        for (int right = 0; right < types.length; right++) {
            if (right > 0 && types[right - 1] != types[right]) {
                long entering = transitionKey(types[right - 1], types[right]);
                frequency.put(entering, frequency.getOrDefault(entering, 0) + 1);
            }

            while (frequency.size() > k) {
                if (left < right && types[left] != types[left + 1]) {
                    long leaving = transitionKey(types[left], types[left + 1]);
                    int count = frequency.get(leaving);
                    if (count == 1) frequency.remove(leaving);
                    else frequency.put(leaving, count - 1);
                }
                left++;
            }

            if (right + 1 - left > bestRight - bestLeft) {
                bestLeft = left;
                bestRight = right + 1;
            }
        }

        return new int[]{bestLeft, bestRight};
    }
}
