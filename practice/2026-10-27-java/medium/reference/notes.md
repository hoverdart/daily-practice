# Reference Notes — Budgeted Distinct Signal Windows

## Recognition signals

"Count contiguous windows," "nonnegative costs," and "at most" constraints signal a frequency-map sliding window. "Exactly k distinct" signals subtracting **at most k-1** from **at most k**.

## Brute force versus optimal

Enumerating every pair of endpoints and maintaining a running sum and set takes O(n²) time, O(n) space. Define F(d) as the number of windows with at most d distinct codes **and** cost at most budget. Then F(k)-F(k-1) counts exactly k distinct codes: all windows with fewer than k distinct codes appear in both and cancel.

## Core invariant

For each right endpoint, after adding its event and shrinking, [left,right] satisfies both upper bounds. Because costs are nonnegative and removing an element cannot increase the distinct count, every suffix ending at right and starting at or after left is valid. Every earlier start is invalid: the previous left was advanced only while the window violated a bound, and adding back elements cannot restore validity. Exactly right-left+1 valid windows end at right.

## Complexity

Two passes, each O(n) expected time with HashMap operations. left and right each advance at most n times, so nested while loops are amortized linear. O(n) auxiliary map space worst case. Use long: 100,000*100,001/2 exceeds Integer.MAX_VALUE.

## Common mistakes

- Counting only the longest window ending at right, rather than all valid suffixes.
- Trying to maintain exactly k as the shrink condition; exactly k is not downward closed.
- Keeping zero-frequency map entries.
- Shrinking for only one of the two bounds.
- Mishandling k=0, zero costs, or empty arrays.
- Using int for totalCost or answer.
- Assuming the same technique works with negative costs: removing a negative cost could increase the sum.

## CS61B connections

HashMap representation invariants, amortized two-pointer analysis, and counting via set differences. Compared with October 20's longest window with limited repeated types, this problem counts **all** valid windows and uses distinct-code cardinality.
