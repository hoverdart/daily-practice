import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class TestSolution {
    private static int checks = 0;
    private static final int[] DR = {-1,1,0,0}, DC = {0,0,-1,1};
    private static void eq(int actual, int expected) {
        if (actual != expected)
            throw new AssertionError("expected " + expected + ", got " + actual);
        checks++;
    }
    private static char[][] grid(String... lines) {
        char[][] a = new char[lines.length][];
        for (int r = 0; r < a.length; r++) a[r] = lines[r].toCharArray();
        return a;
    }
    private static char[][] copy(char[][] a) {
        char[][] b = new char[a.length][];
        for (int r = 0; r < a.length; r++) b[r] = a[r].clone();
        return b;
    }
    private static void check(char[][] a, int expected) {
        char[][] old = copy(a);
        eq(Solution.minimumEscapeMinutes(a), expected);
        if (!Arrays.deepEquals(old, a)) throw new AssertionError("mutated grid");
    }
    // Small independent time-step simulator. Rather than shortest flood
    // distances, it explicitly spreads flooded tiles each minute and enumerates
    // all human states reachable at the end of that minute.
    private static int oracle(char[][] a) {
        int rows = a.length, cols = a[0].length, cells = rows*cols;
        boolean[][] wet = new boolean[rows][cols];
        int start = -1, exit = -1;
        for (int r = 0; r < rows; r++) for (int c = 0; c < cols; c++) {
            if (a[r][c] == 'F') wet[r][c] = true;
            if (a[r][c] == 'S') start = r*cols+c;
            if (a[r][c] == 'E') exit = r*cols+c;
        }
        Set<Integer> frontier = new HashSet<>();
        frontier.add(start*2);
        for (int minute = 0; minute <= 2*cells; minute++) {
            if (frontier.isEmpty()) return -1;
            for (int state : frontier) if (state/2 == exit) return minute;
            if (minute == 2*cells) break;
            boolean[][] nextWet = new boolean[rows][cols];
            for (int r = 0; r < rows; r++) nextWet[r] = wet[r].clone();
            for (int r = 0; r < rows; r++) for (int c = 0; c < cols; c++) {
                if (!wet[r][c]) continue;
                for (int d = 0; d < 4; d++) {
                    int nr = r+DR[d], nc = c+DC[d];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
                            && a[nr][nc] != '#') nextWet[nr][nc] = true;
                }
            }
            Set<Integer> next = new HashSet<>();
            for (int state : frontier) {
                int cell = state/2, used = state&1;
                int r = cell/cols, c = cell%cols;
                for (int d = 0; d < 4; d++) {
                    int nr = r+DR[d], nc = c+DC[d];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                    if (a[nr][nc] == '#' || nextWet[nr][nc]) continue;
                    int newUsed = used + (a[nr][nc] == 'G' ? 1 : 0);
                    if (newUsed <= 1) next.add(2*(nr*cols+nc)+newUsed);
                }
            }
            frontier = next;
            wet = nextWet;
        }
        return -1;
    }
    public static void main(String[] args) {
        check(grid("SE"), 1);
        check(grid("S.G.E"), 4);
        check(grid("S.G.GE"), -1);
        check(grid("S.E","F##"), 2);
        check(grid("S.E","..F"), -1);
        check(grid("S#E"), -1);
        check(grid("S.G#E"), -1);
        check(grid("S.F.E"), -1);
        check(grid("S...E"), 4);
        check(grid("SF","GE"), -1); // flood reaches E at minute 1

        Random rng = new Random(20261110);
        for (int trial = 0; trial < 1_200; trial++) {
            int rows = 1 + rng.nextInt(5), cols = 1 + rng.nextInt(5);
            if (rows*cols == 1) cols = 2;
            char[][] a = new char[rows][cols];
            for (int r = 0; r < rows; r++) for (int c = 0; c < cols; c++) {
                int x = rng.nextInt(12);
                a[r][c] = x < 2 ? '#' : x < 5 ? 'G' : x < 7 ? 'F' : '.';
            }
            int s = rng.nextInt(rows*cols);
            int t = rng.nextInt(rows*cols-1);
            if (t >= s) t++;
            a[s/cols][s%cols] = 'S';
            a[t/cols][t%cols] = 'E';
            check(a, oracle(a));
        }

        int side = 240;
        char[][] large = new char[side][side];
        for (int r = 0; r < side; r++) Arrays.fill(large[r], '.');
        large[0][0] = 'S';
        large[side-1][side-1] = 'E';
        check(large, 2*(side-1)); // long obstacle-free path, no flood
        large[0][1] = 'G';
        large[1][0] = 'G';
        check(large, 2*(side-1)); // either first step spends the single permit

        System.out.println("PASS hard: " + checks + " checks");
    }
}
