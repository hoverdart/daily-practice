# Reasoning

**Recognition:** contiguous intervals + a validity rule that cannot worsen on deletion or improve on extension -> sliding window. Here count windows, not just the longest. A bounded ID universe allows a direct-address frequency array instead of a hash table.

**Baseline:** enumerate all intervals and recompute frequencies, O(n^3+n^2 U) if clearing/scanning U counters each time. Incrementally extend each left boundary, updating repeated IDs in O(1), reducing to O(n^2+nU) time. Better: reuse the frequency table between neighboring right boundaries.

**Invariant:** freq describes exactly [left,right]; repeated counts IDs with frequency >=2. On insert, only 1->2 adds a repeated ID; on removal, only 2->1 removes one. Shrink while invalid, never reset the entire window. After shrinking, left is the earliest valid start: starts discarded earlier remain invalid for a later right because adding IDs never reduces repeated count. Every suffix starting at left..right is valid because deletion cannot increase the count. Therefore add right-left+1 windows exactly once. Example [0,0,1,1], k=1: contributions 1,2,3,3 = 9.

**Complexity:** O(n+U) time (zero-initialize U counters, each index enters/leaves at most once), O(U) extra space. Max total n(n+1)/2 = 20,000,100,000 for n=200000, so use long long.

**Common mistakes:** confuse repeated IDs with equal pairs or extra occurrences; decrement repeated on every removal; shrink with if rather than while; add window length only once at end; use int total; forget free or allocate using sizeof(pointer). For IDs with huge/sparse ranges consider a hash table.

**CS61B:** array indexing vs hash maps, amortized analysis, invariant-driven design, direct-address tables and their space tradeoffs. Explain why the nested loop is linear without claiming each iteration is constant.
