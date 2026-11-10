import java.util.ArrayDeque;
import java.util.Deque;

public class Solution {
    public static int[] processInbox(int[][] commands) {
        int queries = 0;
        for (int[] cmd : commands) {
            if (cmd[0] == 2 || cmd[0] == 3) queries++;
        }
        int[] answers = new int[queries];
        int at = 0;

        Deque<Integer> incoming = new ArrayDeque<>();
        Deque<Integer> outgoing = new ArrayDeque<>();
        for (int[] cmd : commands) {
            if (cmd[0] == 1) {
                incoming.push(cmd[1]);
                continue;
            }
            if (outgoing.isEmpty()) {
                while (!incoming.isEmpty()) {
                    outgoing.push(incoming.pop());
                }
            }
            if (outgoing.isEmpty()) {
                answers[at++] = -1;
            } else if (cmd[0] == 2) {
                answers[at++] = outgoing.pop();
            } else {
                answers[at++] = outgoing.peek();
            }
        }
        return answers;
    }
}
