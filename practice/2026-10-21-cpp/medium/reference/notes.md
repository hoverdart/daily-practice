# Reference notes — Longest Low-Collision Window

## Recognition signals
Keywords **longest contiguous interval**, **at most a budget**, and a statistic that never increases when elements are removed indicate a variable-length sliding window. The subtlety is the statistic: equal-ID **pairs**, not merely the number of duplicated IDs.

## Brute force versus optimal
Enumerate all O(n²) windows and count equal pairs in O(length²), giving O(n⁴) for a literal four-loop solution. Reusing a frequency table while extending each fixed left boundary gives O(n²) expected time. Instead keep one growing/shrinking window with a hash table and maintain pair count incrementally.

## Core invariants
After processing `right` and completing the shrink loop, `freq[x]` equals the count of x in `ids[left..right]`, and `pairs = sum_x freq[x]*(freq[x]-1)/2 <= k`.

- Add x with old frequency f: the new occurrence pairs with each of f previous occurrences, so `pairs += f`, then `freq[x]++`.
- Remove y with old frequency f: decrement first, leaving f-1, then `pairs -= f-1`. Erase zero-frequency keys to keep map size bounded by current distinct IDs.
- While pairs > k, advance left. Removing cannot create collision pairs; eventually the window is valid.
- After shrinking, compare `right+1-left` to best length. Only replace on **strictly greater** length: as right advances, left never decreases, so the first max-length window has the earliest start.

## Complexity and correctness
Each right position is inserted once and each left position removed at most once: O(n) expected time with `unordered_map` (adversarial hash collisions can worsen it), O(d) extra memory for d distinct values in the current window. At n=200000, all equal gives n(n-1)/2 = 19,999,900,000 pairs, exceeding signed 32-bit int. Use `long long`. For a fixed right, shrinking only as much as necessary leaves the longest valid window ending at right, so considering each right finds the global optimum.

## Common mistakes
- Increment the pair count by 1 for every duplicate, rather than by its **existing frequency**.
- On removal subtract old f rather than f-1.
- Forget to erase zero-count entries, inflating retained memory.
- Update best before repairing an invalid window.
- Treat [left,right] as half-open or return right rather than right+1.
- Use int for pair count, overflow near 200k identical IDs.
- Reset left to zero per right (quadratic) or update best on ties (wrong earliest index).

## CS61B and C++ connections
CS61B hashing: `unordered_map<int,int>` provides average constant-time lookup and updates, with load factor/collision tradeoffs. The amortized two-pointer argument resembles amortized resizing: although there is a nested loop, each index moves O(1) times. `std::pair<int,int>` returns the interval, `long long` protects arithmetic, and `auto it = freq.find(y)` avoids accidental insertion when removing.
