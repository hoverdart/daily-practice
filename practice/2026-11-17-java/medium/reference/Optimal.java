import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int[] longestFairSession(int[] workerIds,
                                           int maxPerWorker,
                                           int minDistinct) {
        Map<Integer, Integer> frequency = new HashMap<>();
        int left = 0;
        int bestLeft = -1;
        int bestRight = -1;
        int bestLength = 0;

        for (int right = 0; right < workerIds.length; right++) {
            int id = workerIds[right];
            frequency.put(id, frequency.getOrDefault(id, 0) + 1);

            // Previously all counts were within cap. Only the incoming ID can exceed it.
            while (frequency.get(id) > maxPerWorker) {
                int leaving = workerIds[left++];
                int remaining = frequency.get(leaving) - 1;
                if (remaining == 0) frequency.remove(leaving);
                else frequency.put(leaving, remaining);
            }

            int length = right - left + 1;
            if (frequency.size() >= minDistinct
                    && (length > bestLength
                        || (length == bestLength
                            && (bestLeft == -1 || left < bestLeft)))) {
                bestLength = length;
                bestLeft = left;
                bestRight = right;
            }
        }

        return new int[]{bestLeft, bestRight};
    }
}

