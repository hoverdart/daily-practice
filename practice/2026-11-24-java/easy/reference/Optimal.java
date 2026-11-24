import java.util.Arrays;

public class Solution {
    public static int[] previousHigher(int[] priority) {
        int n = priority.length;
        int[] result = new int[n], stack = new int[n];
        Arrays.fill(result, -1);
        int size = 0;
        for (int i = 0; i < n; i++) {
            while (size > 0 && priority[stack[size - 1]] <= priority[i]) size--;
            if (size > 0) result[i] = stack[size - 1];
            stack[size++] = i;
        }
        return result;
    }
}
