# Minimum Boot Stations for a One-Way Network (Hard / Stretch)

A one-way relay network has `n` stations numbered `0..n-1`. Each directed link `[u,v]` means an **active** station `u` will eventually activate `v`. Activation may propagate along any number of outgoing links.

You may manually boot a set of stations. Find the **smallest number of boots** that eventually activates **every** station. Return the chosen station IDs in **ascending order**. When several stations in a mutually reachable group could serve as its boot, choose the **smallest-numbered** station in that group. This tie rule makes the answer unique.

~~~java
public static int[] minimumBootStations(int n, int[][] links)
~~~

**Example**

~~~text
n = 5
links = [[0,1],[1,0],[2,3],[3,2],[1,2],[4,3]]

Strongly connected groups: {0,1}, {2,3}, {4}
Cross-group links: {0,1} -> {2,3} and {4} -> {2,3}
answer: [0,4]  // two independent source groups must be booted
~~~

**Constraints:** `0 <= n <= 120_000`, `0 <= links.length <= 250_000`; endpoint IDs are valid; self-loops and duplicate edges are allowed. Do not modify `links`. Aim for **O(n+m) time and O(n+m) space**; recursion depth can reach `n`, so avoid relying on Java's call stack.

**Interview checkpoints:** Why isn't counting indegree-zero **vertices** sufficient? What makes a directed cycle act like a single unit? What is a strongly connected component? Why does one representative from each zero-indegree SCC suffice?