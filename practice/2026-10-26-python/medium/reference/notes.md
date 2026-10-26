# Longest Affordable Channel Window — Reference Notes

## Recognition signals
The question asks for a **longest contiguous** segment satisfying two constraints that cannot become worse when elements are removed: distinct-channel count and sum of **nonnegative** costs. This signals a variable-length sliding window. Unlike a set, a **frequency dictionary** supports removing one occurrence while retaining a channel that appears elsewhere.

## Brute force → optimal
Enumerate each start and extend each end, tracking a running cost and channel counts: O(n²) time (naively recomputing slices can be O(n³)). Optimal: maintain one moving window `[left,right]` and repair violations by moving only `left`.

After appending the event at `right`, repeatedly remove the leftmost event while `total > budget OR len(freq) > max_types`. The repaired window is valid; record it if strictly longer than the previous best.

## Two invariants and proof sketch
1. `freq[x]` is the **positive** number of occurrences of channel x in the current window. Delete keys whose count falls to zero; then `len(freq)` equals the distinct-channel count.
2. `total` is the sum of costs in the current window.
3. Once the shrink loop ends, both constraints hold. Any window ending at `right` and starting earlier than `left` was eliminated when it violated a monotone constraint; it cannot be valid.

Because costs are nonnegative, removing an event never raises cost. Removing an event never increases distinct count either. Each event enters once and leaves at most once, making the nested loop amortized linear.

For `[1,2,1,3,1]` with costs `[2,1,1,1,2]`, k=2, budget=4: `[0,3)` is valid (sum 4). Extending to channel 3 forces a shrink past channel 2; the later `[2,5)` is also length 3, so retain earliest start 0.

## Complexity
Expected O(n) time, O(d) frequency-map space where d is at most the number of distinct channels in a transient window, and O(n) worst-case auxiliary space. Returned indices take O(1) output space. Hash-map operations are expected constant time.

## Common mistakes
- Shrinking only when **both** constraints fail instead of **either**.
- Using a set and deleting a channel while another copy remains.
- Forgetting `del freq[x]` at count zero, leaving a false distinct type.
- Updating best **before** restoring validity.
- Updating on equal lengths, which can overwrite the earliest start.
- Treating the cost limit as monotone when negative costs are permitted.
- Off-by-one confusion: returned interval is **half-open** `[left,right)`, but loop variable `right` is inclusive.

## CS61B connections / Python recall
The frequency dictionary is a hash table storing counts, not just membership. The moving endpoints illustrate amortized analysis: a nested loop need not imply O(n²) when each pointer advances at most n times. Python `dict.get(key,0)` supplies the default, `del freq[key]` removes an exhausted channel, and `len(freq)` counts **keys**. Compare your October 5 attempt, where the purpose of the frequency dictionary was unclear.
