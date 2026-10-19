# Low-Load Processing Batches — Reference Notes

## Recognition signals
"Count contiguous segments satisfying a **monotone** bound" + **strictly positive** entries → two pointers/sliding window. Multiplying by a positive integer ≥1 never decreases the product, and removing a leftmost factor never increases it. This monotonicity makes the technique safe.

## Brute force → optimal
Enumerate every starting index, multiply successively as you move right, and count products < limit: O(n²) time, O(1) extra space. Avoid re-multiplying every slice from scratch.

Optimal: maintain the product of exactly loads[left:right+1]. For each right, include the new value, then advance left while product >= limit. When the window is valid, **all its suffixes ending at right** are valid; there are right-left+1 choices of starting position. Add that number to the answer.

## Invariant and trace
After the while loop, the maintained window is valid, and every longer segment ending at right (starting before left) is invalid. Thus left is the earliest valid start for this right.

For [10,5,2,6], limit 100:
- right 0: [10], 1 valid suffix.
- right 1: [10,5], 2 suffixes.
- right 2: product 100, drop 10 → [5,2], 2 suffixes.
- right 3: [5,2,6], 3 suffixes.
Total 1+2+2+3=8.

Because all loads are ≥1, limit ≤1 admits **no** nonempty valid segment. Return 0 immediately. If a single value is too large, shrinking can make left=right+1; that empty window contributes zero, and the next iteration still works.

## Complexity
Each right increments once; each left increments at most n times across the entire run: O(n) pointer steps, O(1) auxiliary space. Integer arithmetic is assumed constant-cost for bounded inputs; Python big-integer costs can add bit-complexity for enormous values, though the shrinking invariant keeps products bounded by roughly limit times the current input.

## Common mistakes
- Using <= instead of <; the loop must shrink while product >= limit.
- Adding only 1 per right instead of right-left+1.
- Forgetting the limit ≤1 guard.
- Using floating-point division instead of exact integer //.
- Treating nested while as O(n²): pointers never move backward.
- Applying this product window to zero or negative loads without revisiting monotonicity.

## CS61B connections / Python recall
This is a **two-pointer amortized** argument analogous to resizing and deque amortization in CS61B. It revisits the October 5 sliding-window 2/5 weakness, but without a frequency dictionary: focus on what state describes the current window, when to repair it, and when to count answers. Python: enumerate(loads), product //= loads[left], and early return for degenerate bounds.

