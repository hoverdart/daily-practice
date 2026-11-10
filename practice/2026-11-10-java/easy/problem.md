# Two-Stack Alert Inbox (Easy)

An operations team receives alerts in the order they arrive. The interface supports enqueue, dequeue, and peek, but your implementation may use **only two LIFO stacks** as its persistent storage (use java.util.ArrayDeque with push/pop/peek, not queue methods). Implement FIFO semantics despite each individual stack being LIFO.

~~~java
public static int[] processInbox(int[][] commands)
~~~

Each command has two integers [type, value]:
- [1, ticket] — append a ticket to the back of the inbox; 1 <= ticket <= 1_000_000_000.
- [2, 0] — remove and return the oldest ticket, or -1 if empty.
- [3, 0] — return the oldest ticket without removing it, or -1 if empty.

Return an array containing one answer for every type 2 or type 3 command, in command order. Never modify the commands input.

Example:

~~~text
commands = [[1,10],[1,20],[3,0],[2,0],[1,30],[2,0],[2,0],[2,0]]
answers  = [10,10,20,30,-1]
~~~

Constraints: 0 <= commands.length <= 200_000. Each command is well formed. You may not replace the two stacks with an actual queue or store all pending tickets in an array/list. Target **O(q) total time** for q commands (amortized O(1) per operation) and O(q) worst-case auxiliary space.

Interview checkpoints: Which stack holds new tickets? When exactly do you transfer? Why transfer **only** when the output stack is empty? How can one expensive transfer still give O(1) amortized operations?
