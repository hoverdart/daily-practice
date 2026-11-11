# Medium solution notes — Longest Trace With Limited Repeated Handoffs

## Recognition signals

- **Longest contiguous** portion under an **at most k** constraint implies a variable-size sliding window when removing the leftmost item cannot worsen validity.
- The tracked objects are **edges between consecutive visits**, not the visits themselves. Moving either endpoint changes at most one edge.
- Handoff direction is irrelevant, so canonicalize every pair as (min(a,b), max(a,b)). Repeated visits (a,a) remain valid edges.

## Brute force versus optimal

**Brute force:** enumerate each start and extend each end, storing handoff frequencies. Stop extending when repeats exceeds k, because a longer window cannot reduce repeat count. O(n²) time and O(n) space in the worst case.

**Optimal sliding window:** maintain freq[edge] and a scalar repeats equal to sum(max(0,freq[edge]-1)). At each right endpoint, add the new adjacent handoff. If repeats > k, repeatedly remove the leftmost handoff until valid. Update the best valid span. Hash operations are expected O(1); each end moves at most n times, giving expected **O(n) time**, O(n) worst-case auxiliary space. Pathological unordered_map collisions can worsen the runtime.

## State-update rules

For an edge frequency f before adding:
- f == 0: adding its first copy contributes no repeat.
- f >= 1: adding one more copy increases repeats by 1.

For an edge frequency f before removing:
- f == 1: removing its only copy contributes no repeat change.
- f >= 2: removing one repeated copy decreases repeats by 1.

These four cases are the heart of the proof, not a memorized sliding-window template.

## Correctness invariant

After finishing each right endpoint, the map counts exactly the handoffs inside visits [left,right], and repeats equals their total excess occurrences. The shrinking loop yields the **smallest valid left endpoint** for that right endpoint: every earlier left yields a strictly larger, invalid window, since deletion cannot increase repeats. Thus this window is the longest valid one ending at right. Taking its length at every right finds a global maximum. Scanning right in order and updating only when length strictly improves yields the earliest start on ties.

## C++ syntax you can reuse

~~~cpp
std::unordered_map<std::uint64_t, int> freq;
int& count = freq[key];           // defaults missing keys to zero
if (count >= 1) ++repeats;
++count;
// On removal, first find the entry so you do not insert a missing key:
auto it = freq.find(key);
if (it->second > 1) --repeats;
if (--it->second == 0) freq.erase(it);
~~~

The reference creates an injective 64-bit key from two **signed-sorted** 32-bit values. Casting signed int to uint32_t preserves the unique 32-bit residue representation, including negatives. Packing with a 32-bit shift avoids lossy string concatenation and narrowing.

## Common mistakes

1. Counting repeat **vertices** instead of repeat handoff **types**.
2. Treating reversed edges as different types.
3. Decreasing repeats when a unique edge leaves.
4. Removing the wrong edge when left advances: remove stations[left] -> stations[left+1], then increment left.
5. Failing to erase zero-count entries; the map grows misleadingly large.
6. Updating the winner on >= length overwrites the earliest tie.
7. Using signed left shifts on negative IDs (undefined behavior).

## CS61B connection

This directly combines CS61B hash-table frequency counting, graph edge canonicalization for undirected graphs, deque/window invariants, and amortized pointer progress. It revisits the older sliding-window difficulty with a different counted entity from prior event-frequency problems. Explain the invariant aloud before inspecting the reference.
