public class Solution {
    public static long[] applyPatches(int n, int[][] patches) {
        long[] difference = new long[n + 1];
        for (int[] patch : patches) {
            int left = patch[0], right = patch[1];
            long delta = patch[2];
            difference[left] += delta;
            difference[right + 1] -= delta;
        }

        long[] answer = new long[n];
        long running = 0L;
        for (int i = 0; i < n; i++) {
            running += difference[i];
            answer[i] = running;
        }
        return answer;
    }
}
