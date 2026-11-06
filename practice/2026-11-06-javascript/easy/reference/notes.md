# Nearest Blocking Beacon — Recognition, Proof, and Notes

## Recognition signals

"Nearest earlier", "first greater-or-equal to the left", and "all positions" suggest a **monotonic stack of indices** rather than repeated scans. The output asks for indices; preserve indices instead of storing only strengths.

## Brute force vs optimal

**Brute force:** For each i, check i-1, i-2, ... until finding a strength >= strengths[i]. Worst-case O(n²) time, O(n) space for output.

**Optimal:** Maintain a stack of indices with **nonincreasing strengths from bottom to top**. Before answering i, pop indices strictly weaker than strengths[i]. The remaining top, if any, is its closest qualifying earlier index. Push i afterward. Equal strengths must stay: they qualify and the most recent equal value should win.

## Invariant and correctness

Before pushing i, the stack contains increasing indices with nonincreasing strengths, after all earlier indices made permanently irrelevant by later stronger readings have been removed. Every popped j has a newer beacon i with strictly greater strength. For any future k>i with strength <= strengths[j], i is closer than j and also qualifies. For any future k whose strength exceeds strengths[j], j cannot qualify anyway. Thus j will never be a correct future answer. The top remaining index is the closest eligible predecessor, since anything later was popped and did not qualify.

## Complexity

Each index is pushed once and popped at most once: O(n) time (amortized), O(n) stack plus O(n) output. No recursion is needed even for 150,000 beacons.

## Common mistakes

- Popping on <= rather than < discards equal blockers.
- Storing only values loses the required index.
- Confusing "nearest to the left" with "maximum strength on the left".
- Reporting a distance i-j instead of the requested index.
- Claiming O(n²) because of nested loops: charge each pop to the unique pushed index.
- Mutating the input or reversing it and forgetting to convert indices.

## CS61B connection

This is a stack/ArrayDeque-style LIFO data structure plus amortized reasoning (each element can incur only one push and one pop). The stack encodes dominance: a later, stronger beacon makes certain earlier entries irrelevant. Similar invariants appear in next-greater-element, daily-temperature, and histogram algorithms.
