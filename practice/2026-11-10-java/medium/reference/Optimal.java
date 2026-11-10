import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static long countAffordableBursts(int[] channel, int[] cost,
                                             int maxDistinct, long budget) {
        Map<Integer, Integer> frequency = new HashMap<>();
        int left = 0;
        long runningCost = 0L;
        long total = 0L;
        for (int right = 0; right < channel.length; right++) {
            int id = channel[right];
            frequency.put(id, frequency.getOrDefault(id, 0) + 1);
            runningCost += cost[right];
            while (frequency.size() > maxDistinct || runningCost > budget) {
                int removeId = channel[left];
                int remaining = frequency.get(removeId) - 1;
                if (remaining == 0) frequency.remove(removeId);
                else frequency.put(removeId, remaining);
                runningCost -= cost[left];
                left++;
            }
            total += right - left + 1L;
        }
        return total;
    }
}
