import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class TestSolution {
    private static int checks;
    private static void eq(int[] actual, int[] expected) {
        if (!Arrays.equals(actual, expected)) {
            throw new AssertionError("expected " + Arrays.toString(expected)
                    + "; got " + Arrays.toString(actual));
        }
        checks++;
    }
    // Deliberately different oracle: use a real FIFO queue.
    private static int[] oracle(int[][] commands) {
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        ArrayList<Integer> out = new ArrayList<>();
        for (int[] command : commands) {
            if (command[0] == 1) queue.addLast(command[1]);
            else if (command[0] == 2) {
                Integer x = queue.pollFirst();
                out.add(x == null ? -1 : x);
            } else {
                Integer x = queue.peekFirst();
                out.add(x == null ? -1 : x);
            }
        }
        int[] a = new int[out.size()];
        for (int i = 0; i < a.length; i++) a[i] = out.get(i);
        return a;
    }
    private static int[][] copy(int[][] src) {
        int[][] clone = new int[src.length][];
        for (int i = 0; i < src.length; i++) clone[i] = src[i].clone();
        return clone;
    }
    private static void check(int[][] commands, int[] expected) {
        int[][] snapshot = copy(commands);
        eq(Solution.processInbox(commands), expected);
        if (!Arrays.deepEquals(snapshot, commands)) throw new AssertionError("mutated commands");
    }

    public static void main(String[] args) {
        check(new int[][]{}, new int[]{});
        check(new int[][]{{2,0},{3,0}}, new int[]{-1,-1});
        check(new int[][]{{1,10},{1,20},{3,0},{2,0},{1,30},
                {2,0},{2,0},{2,0}}, new int[]{10,10,20,30,-1});
        check(new int[][]{{1,99},{3,0},{3,0},{2,0},{3,0}},
                new int[]{99,99,99,-1});
        check(new int[][]{{1,1},{2,0},{1,2},{1,3},{2,0},
                {1,4},{3,0},{2,0},{2,0}}, new int[]{1,2,3,3,4});
        Random rng = new Random(20261110);
        for (int trial = 0; trial < 1_700; trial++) {
            int n = rng.nextInt(90);
            int[][] commands = new int[n][2];
            for (int i = 0; i < n; i++) {
                int type = 1 + rng.nextInt(3);
                commands[i][0] = type;
                commands[i][1] = type == 1 ? 1 + rng.nextInt(100) : 0;
            }
            check(commands, oracle(commands));
        }

        int count = 100_000;
        int[][] stress = new int[2 * count][2];
        for (int i = 0; i < count; i++) stress[i] = new int[]{1,i+1};
        for (int i = count; i < 2 * count; i++) stress[i] = new int[]{2,0};
        int[] got = Solution.processInbox(stress);
        if (got.length != count) throw new AssertionError("wrong stress length");
        for (int i = 0; i < count; i++) {
            if (got[i] != i+1) throw new AssertionError("wrong FIFO order at " + i);
        }
        checks++;
        System.out.println("PASS easy: " + checks + " checks");
    }
}
