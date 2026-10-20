import java.util.ArrayDeque;
import java.util.Deque;

public class Solution {
    public static int[] secondsUntilHigher(int[] readings) {
        int n = readings.length;
        int[] answer = new int[n];
        Deque<Integer> unresolved = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            while (!unresolved.isEmpty()
                    && readings[i] > readings[unresolved.peek()]) {
                int previous = unresolved.pop();
                answer[previous] = i - previous;
            }
            unresolved.push(i);
        }
        return answer;
    }
}
