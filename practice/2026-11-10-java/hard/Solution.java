import java.util.ArrayDeque;
import java.util.Arrays;

public class Solution {
    public static int minimumEscapeMinutes(char[][] grid) {
        // TODO:
        // 1. Multi-source BFS from all F cells to compute earliest flood arrival.
        // 2. BFS from S over (cellIndex, permitUsed=0/1) states.
        // 3. Enter neighbors only when arrivalTime < floodTime (or never flooded).
        // 4. Visiting G increases permitUsed; cap at 1.
        // Return -1 when no safe escape exists. Do not mutate grid.
        throw new UnsupportedOperationException("Implement minimumEscapeMinutes");
    }
}
