# Reference notes — Filter Invalid Routing Markers

## Recognition signals

Nested opening/closing tokens, a need to match earlier unmatched opening tokens, and a final cleanup pass suggest **a stack of indices**. Ordinary characters are inert payloads.

## Brute force versus optimal

A brute-force approach tries every subset of parentheses removed; there can be `2^p` subsets for `p` parentheses, and checking each candidate costs O(n). A less extreme repeated string-deletion strategy can still become O(n²) from copying.

**Optimal:** scan once, pushing indices of open markers; for `)`, pop an opening index if one exists, otherwise mark that close for deletion. Leftover stack indices are unmatched openings, so mark them too. Rebuild the answer by ignoring marked positions. Every retained pair is properly nested; no mismatched marker can remain.

## Complexity and invariant

- Time **O(n)**: each character visited a constant number of times, each opening pushed and popped at most once.
- Additional space **O(n)**: stack + removal flags + output.
- Invariant after processing prefix `[0,i]`: stack holds exactly the indices of unmatched opening markers in that prefix; every discarded closing bracket lacks a possible earlier match.

## Common mistakes

- Mistakenly deleting *all* opening brackets that don't have an immediately adjacent `)`.
- Marking valid opening brackets for deletion before later closing brackets arrive.
- Using `shift()` or rebuilding substrings repeatedly, causing quadratic copying.
- Losing letters or changing their order; return the unmodified string when already valid.
- Assuming `)` at the beginning might become valid because an opening bracket appears later.

## CS61B connections

This is the push/pop stack invariant from ADT implementations and parentheses parsing. The output reconstruction resembles the linear scan used when filtering an array list or linked sequence. For a second solution, try a left-to-right filter followed by right-to-left unmatched-open elimination and prove it is equivalent.

