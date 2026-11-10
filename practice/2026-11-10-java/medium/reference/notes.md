# Reference notes — Count Affordable Mixed-Channel Bursts

## Recognition signals

The task asks for the **number of contiguous intervals** satisfying two upper-bound constraints. Both constraints can only become easier as we remove an event from the left: nonnegative costs never increase upon removal, and removing an event cannot increase the number of distinct IDs. That monotonicity enables a variable-size sliding window.

This is spaced repetition for the previously reported 2/5 window-frequency-map confusion, but with **two constraints and an interval-count output** rather than one longest/minimum window.

## Baseline vs optimal

Brute force: enumerate each pair (l,r), build or update a distinct-ID set and accumulated cost while extending r. Time O(n²) expected and O(d) memory; rechecking every interval from scratch would be even slower.

Optimal: scan right from 0 to n-1. Add channel[right] to a frequency HashMap and add cost[right] to a long sum. While distinct count > maxDistinct **or** sum > budget, remove channel[left] (decrement and delete if zero), subtract cost[left], then left++.

**Counting trick:** after restoring validity, [left..right] is valid and every suffix [s..right] with s >= left is also valid. Every s < left is invalid, because the scan moved left forward only when the old prefix violated a constraint, and extending the right endpoint cannot repair a violation under these assumptions. Thus exactly right-left+1 valid nonempty windows end at right. Add that quantity to a long total.

Time O(n) **expected** from O(1) average HashMap operations: each pointer moves at most n steps. Memory O(d), where d <= n is the maximum number of distinct channels in the active window. Output counts can reach n(n+1)/2, e.g. 20,000,100,000 at n=200,000, so return long.

## Invariant

At the end of processing each right:
- frequency[id] is exactly the number of occurrences of id in [left..right]; no zero counts remain.
- runningCost equals the sum of cost[left..right].
- both constraints hold; left is the smallest index giving a valid window ending at right (or right+1 if no nonempty window works).

## Java syntax

~~~java
Map<Integer,Integer> freq = new HashMap<>();
freq.put(id, freq.getOrDefault(id, 0) + 1);
int c = freq.get(id) - 1;
if (c == 0) freq.remove(id);
else freq.put(id, c);
long count = 0L;   // not int
~~~

## Common mistakes

- Keeping zero-count entries; HashMap.size then overcounts distinct IDs.
- Shrinking only when **both** limits are exceeded instead of when either is.
- Adding 1 for each valid right rather than right-left+1.
- Using int for sum or answer, which can overflow.
- Forgetting that maxDistinct = 0 forces empty window, which contributes zero nonempty windows.
- Applying this exact algorithm to negative costs: a longer window can then become cheaper, breaking the monotonicity used to discard earlier starts.

## CS61B connections

Hash-table frequency bookkeeping and average-case constant-time operations, arrays and index invariants, amortized analysis of moving pointers, and prefix/suffix counting. Compare the window technique to CS61B graph traversals: each element is inserted and removed at most once despite nested loops.
