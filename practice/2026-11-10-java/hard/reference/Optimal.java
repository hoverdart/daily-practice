import java.util.ArrayDeque;
import java.util.Arrays;

public class Solution {
    public static int minimumEscapeMinutes(char[][] grid) {
        int rows = grid.length, cols = grid[0].length;
        int cells = rows * cols;
        int[] floodAt = new int[cells];
        Arrays.fill(floodAt, -1);

        // Flood BFS: all flooded cells at time zero are sources.
        int[] queue = new int[cells];
        int head = 0, tail = 0;
        int start = -1, exit = -1;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int cell = r * cols + c;
                if (grid[r][c] == 'F') {
                    floodAt[cell] = 0;
                    queue[tail++] = cell;
                } else if (grid[r][c] == 'S') start = cell;
                else if (grid[r][c] == 'E') exit = cell;
            }
        }
        int[] dr = {1, -1, 0, 0};
        int[] dc = {0, 0, 1, -1};
        while (head < tail) {
            int cell = queue[head++];
            int r = cell / cols, c = cell % cols;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols
                        || grid[nr][nc] == '#') continue;
                int next = nr * cols + nc;
                if (floodAt[next] != -1) continue;
                floodAt[next] = floodAt[cell] + 1;
                queue[tail++] = next;
            }
        }

        // Human BFS: state = (cell * 2 + gatesEntered).
        int[] dist = new int[2 * cells];
        Arrays.fill(dist, -1);
        int[] states = new int[2 * cells];
        head = 0;
        tail = 0;
        dist[start * 2] = 0;
        states[tail++] = start * 2;
        while (head < tail) {
            int state = states[head++];
            int cell = state / 2;
            int usedGate = state & 1;
            int time = dist[state];
            if (cell == exit) return time;
            int r = cell / cols, c = cell % cols;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols
                        || grid[nr][nc] == '#') continue;
                int nextCell = nr * cols + nc;
                int newGateCount = usedGate + (grid[nr][nc] == 'G' ? 1 : 0);
                if (newGateCount > 1) continue;
                int arrival = time + 1;
                if (floodAt[nextCell] != -1 && arrival >= floodAt[nextCell]) continue;
                int nextState = 2 * nextCell + newGateCount;
                if (dist[nextState] != -1) continue;
                dist[nextState] = arrival;
                states[tail++] = nextState;
            }
        }
        return -1;
    }
}
