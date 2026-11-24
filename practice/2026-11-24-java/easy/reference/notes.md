# Previous Higher Priority — Solution notes

## Recognition signals
"Nearest earlier", "strictly greater", and one answer per position suggest a monotonic stack. A running maximum loses the nearest-index requirement; a sorted data structure loses chronological dominance unless augmented.

## Brute force to optimal
Scan backward from every index until a greater priority is found: O(n²) worst case (increasing or equal values), O(1) auxiliary space excluding output. Instead keep a stack of candidate indices. A later event with priority at least as high dominates an older candidate: whenever the older candidate could be strictly greater than some future event, the later event also qualifies and is closer. Therefore the older candidate can be removed permanently.

For each i, pop while the top priority <= priority[i], read the surviving top as the answer (or -1), then push i.

## Invariant and trace
The stack contains increasing indices with strictly decreasing priorities. Every discarded index has a later dominating index, possibly itself dominated later. Hence after popping nonqualifying candidates, the top is the closest qualifying predecessor.

For [8,3,3,5,2,8], stacks of indices after processing each element are [0], [0,1], [0,2], [0,3], [0,3,4], [5]. The equal 3 at index 2 removes index 1.

## Complexity
Each index is pushed once and popped at most once. O(n) total time, O(n) auxiliary stack space and O(n) returned array. This is aggregate/amortized reasoning, not a claim that every individual iteration is constant time.

## Common mistakes
- Popping only strictly smaller values incorrectly accepts equal priorities.
- Returning priority values instead of zero-based indices.
- Checking the answer after pushing the current index.
- Subtracting two arbitrary ints to compare can overflow. Use <= directly.
- Using Stack<Integer> works, but an int[] avoids boxing and is sufficient when capacity is known. ArrayDeque<Integer> is another idiomatic stack.

## CS61B connections
Array-backed lists, stack LIFO invariants, references versus primitive indices, and aggregate analysis. Try changing the comparison for greater-or-equal; for nearest greater to the right, scan backward and maintain the corresponding candidate stack.
