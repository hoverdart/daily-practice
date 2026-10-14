# Reference notes — Longest Repairable Run

## Recognition signals

**Longest contiguous span** with an **at-most-K** budget and a condition restored by moving the left edge signals sliding window. A single integer `faults` replaces the frequency map from previous exercises: it counts zeros *inside the current window*, not the entire prefix.

## Brute force versus optimal

Enumerate every left endpoint, extend right, and count zeros incrementally: O(n²) time, O(1) space. Overlapping windows repeat work. Instead, expand `right`, add a fault if the new element is zero, and shrink `left` until `faults <= k`. Then update the maximum.

## Invariant and correctness

After shrinking, `[left,right]` has at most k faults. Every smaller left endpoint has already been discarded because it made this window invalid, so the current window is the longest valid one ending at this right endpoint. Maximizing across right endpoints finds the global optimum.

## Complexity

O(n) time: right advances n times, and left advances **at most n times total** despite the nested while. O(1) auxiliary space.

## Common mistakes

Counting faults in the entire prefix; shrinking once with if instead of until valid; updating the answer before restoring validity; mishandling k=0 or empty arrays; and unsigned underflow with size_t when subtracting from an empty vector.

## CS61B connections / C++ recall

Two monotone indices yield an amortized O(n) scan, analogous to deque amortized analysis. `const std::vector<int>&` avoids copying input, and `static_cast<int>(status.size())` avoids signed/unsigned comparison. Once the invariant is automatic, replace the fault counter with an unordered_map for arbitrary categories.
