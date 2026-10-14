# Easy — Longest Repairable Run

Given a binary status vector (1 healthy, 0 fault), find the longest contiguous span with at most k faults, since you may repair at most k of them.

Signature: `int longestRepairableRun(const std::vector<int>& status, int k);`

Examples: [1,0,1,0,1], k=1 → 3; [0,0,0], k=0 → 0; [] → 0.

Constraints: n ≤ 200000, 0 ≤ k ≤ n+10. Target O(n) time and O(1) auxiliary space.
