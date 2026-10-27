import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static long countWindows(int[] codes, int[] costs, int k, long budget) {
        if (k <= 0) return 0L;
        return atMost(codes, costs, k, budget)
                - atMost(codes, costs, k - 1, budget);
    }

    private static long atMost(int[] codes, int[] costs, int maxDistinct, long budget) {
        if (maxDistinct < 0) return 0L;
        Map<Integer, Integer> frequency = new HashMap<>();
        long totalCost = 0L;
        long count = 0L;
        int left = 0;

        for (int right = 0; right < codes.length; right++) {
            frequency.put(codes[right], frequency.getOrDefault(codes[right], 0) + 1);
            totalCost += costs[right];
            while (frequency.size() > maxDistinct || totalCost > budget) {
                int leaving = codes[left];
                int old = frequency.get(leaving);
                if (old == 1) frequency.remove(leaving);
                else frequency.put(leaving, old - 1);
                totalCost -= costs[left];
                left++;
            }
            count += right - left + 1L;
        }
        return count;
    }
}
