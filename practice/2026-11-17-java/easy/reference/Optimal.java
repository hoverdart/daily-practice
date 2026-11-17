import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public static int[] earliestUniqueAfterEach(int[] eventIds) {
        Map<Integer, Integer> frequency = new HashMap<>();
        ArrayDeque<Integer> firstArrivals = new ArrayDeque<>();
        int[] result = new int[eventIds.length];

        for (int i = 0; i < eventIds.length; i++) {
            int id = eventIds[i];
            int count = frequency.getOrDefault(id, 0) + 1;
            frequency.put(id, count);
            if (count == 1) firstArrivals.addLast(id);

            while (!firstArrivals.isEmpty()
                    && frequency.get(firstArrivals.peekFirst()) != 1) {
                firstArrivals.removeFirst();
            }
            result[i] = firstArrivals.isEmpty() ? -1 : firstArrivals.peekFirst();
        }
        return result;
    }
}

