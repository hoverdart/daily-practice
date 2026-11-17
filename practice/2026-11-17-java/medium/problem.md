# Longest Fair Worker Session — Medium

An audit log contains a sequence of worker IDs. Select a **nonempty contiguous session** satisfying both requirements:

1. **No worker ID appears more than maxPerWorker times** inside the session.
2. The session contains **at least minDistinct distinct worker IDs**.

Return the inclusive index range [left, right] of the **longest** valid session. If several have the same length, return the one with the **smallest left index** (and then smallest right index). Return [-1, -1] if no session qualifies.

Implement:

~~~java
public static int[] longestFairSession(int[] workerIds,
                                       int maxPerWorker,
                                       int minDistinct)
~~~

Example:

~~~text
workerIds = [4, 7, 4, 9, 7, 4, 8]
maxPerWorker = 2
minDistinct = 3
answer = [1, 6]   // [7,4,9,7,4,8]: two 7s, two 4s, four distinct
~~~

**Constraints:** 0 <= n <= 200,000; -1,000,000,000 <= workerIds[i] <= 1,000,000,000; 1 <= maxPerWorker <= 200,000; 0 <= minDistinct <= 200,000. Distinct counts refer to integer equality. Do not mutate workerIds. An empty input has no nonempty answer even when minDistinct = 0.

Target O(n) **expected** time with hash frequencies and O(min(n, number of distinct IDs)) auxiliary space (excluding output). Carefully explain why the two conditions should **not** both be used as reasons to shrink.

Interview checkpoints: Which requirement is violated by extending the right boundary? Can dropping the leftmost value ever help to reach a *higher* distinct count? What is the longest admissible candidate for each fixed right endpoint?

