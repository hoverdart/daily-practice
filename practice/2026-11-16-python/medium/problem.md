# Medium — Longest Consensus Segment

A monitoring service records a sequence of integer labels. A team may choose **one contiguous segment** and relabel **at most k entries** inside it. The goal is to make every label in that segment equal to a single chosen value.

Return the maximum possible segment length. The segment can be empty only when the whole input is empty. Labels may be negative; a relabel is a change of one entry to any integer. Do not mutate the input.

## Signature

~~~python
def longest_consensus_segment(labels: list[int], k: int) -> int:
    ...
~~~

**Constraints:** 0 ≤ len(labels) ≤ 200,000; 0 ≤ k ≤ len(labels); −10^9 ≤ label ≤ 10^9.

## Examples

~~~python
longest_consensus_segment([7, 3, 7, 7, 3, 3, 7], 1)  # 4
longest_consensus_segment([1, 2, 1, 2, 1, 2], 2)     # 5
longest_consensus_segment([1, 2, 3, 4], 1)           # 2
longest_consensus_segment([4, 4, 4], 0)              # 3
longest_consensus_segment([], 0)                     # 0
~~~

For any segment of length L, the minimum number of changes required equals **L − maximum label frequency in that segment**. Explain why.

Find an expected O(n)-time solution with a sliding window and hash frequencies. A useful optimization allows a cached **maximum frequency ever observed** to remain stale when the left boundary moves. Explain why a stale maximum does not make the returned *best length* incorrect—even if the current physical window is temporarily not feasible.

Challenge: Give the O(n²) all-starting-points baseline and show why the window's left boundary never needs to move backward.
