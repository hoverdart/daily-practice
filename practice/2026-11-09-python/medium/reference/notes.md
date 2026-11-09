# Smallest Complete Sensor Snapshot — Recognition and Detailed Notes

## Recognition signals

The words **contiguous**, **shortest qualifying interval**, **at least k copies of each label**, and **positive quantities** strongly suggest a variable-size two-pointer window with a frequency dictionary. Unlike a fixed-window anagram check, the window size must grow and shrink. Unlike a distinct-count condition, repeated copies matter.

## Brute force versus optimal

**Brute force:** Enumerate all O(n^2) start/end pairs and count frequencies within each slice. Recounting each slice costs up to O(n) per pair, i.e. O(n^3) naive time. Keeping a growing Counter for each left endpoint reduces this to O(n^2 + n*u) expected time. Neither scales to 200,000 events.

**Optimal:** Store a copy of required as the signed balance need. For each tracked ID x:

- need[x] > 0: the current window lacks that many occurrences.
- need[x] == 0: it contains exactly the required number.
- need[x] < 0: it contains surplus occurrences.

Maintain missing = sum(max(0, need[x])) over all requested x. Initially missing = sum(required.values()). For each incoming x, if x is tracked, decrement missing **only if need[x] was positive before decreasing need[x]**. Then decrement need[x]. Ignore unrelated IDs entirely.

While missing == 0, the current window qualifies. Compare (left, right+1) to the best, using its length; then remove events[left]. For a tracked outgoing x, increment need[x] and increment missing only if the updated need[x] is **positive**. Finally increment left.

Use strictly shorter (<), not <=, to preserve the earliest left index when lengths tie. Since right advances monotonically, any later equal-length window starts later.

## Correctness invariant

At the beginning of each inner-loop check, for every tracked x:

    need[x] = required[x] - count(x in events[left:right+1])

and missing equals the total remaining number of required occurrences. Therefore missing == 0 iff the window meets every request.

When a new right endpoint arrives, all possible qualifying windows ending there must have left boundaries at or before the point where removing the next left element would break coverage. Shrinking while valid visits each such candidate; once removal causes missing > 0, further shrinking cannot regain missing items. All candidate optimal windows are therefore considered.

No earlier candidate is lost: future right boundaries can only extend the stream, and both pointers move forward. Choosing the shortest qualifying candidate (then earliest start) yields the required answer.

## Complexity and Python details

Right advances n times; left advances at most n times total, even with the nested while. Each tracked lookup/update is expected O(1) in a Python dict. Initial copy and sum are O(u). Total **expected O(n + u) time** and **O(u) auxiliary space** for the copied dict; a constant number of indices/counters otherwise. Python dict hashing gives expected/typical O(1) operations, not a universal adversarial worst-case guarantee.

A dictionary is preferable to a large array when ID values are sparse or negative. The solution intentionally does not add irrelevant IDs to need, so its size stays u.

## Common mistakes

- Counting only unique IDs rather than matching required multiplicities.
- Forgetting that negative balances represent **surplus**, not missing items.
- Incrementing missing on removal whenever a tracked value leaves, even when several surplus copies remain.
- Forgetting to update the answer *before* removing the outgoing element.
- Using right as an inclusive output end instead of right+1 for the half-open convention.
- Replacing the best answer on an equal-length candidate, breaking earliest-start ties.
- Repeatedly scanning the whole required dict inside each step, which can cost O(n*u).
- Mutating the caller's requested dict instead of copying it.
- Returning a nonempty window for an empty request (answer must be (0,0)).
- Assuming the method works with arbitrary negative additive budget constraints; this algorithm relies specifically on monotonicity of multiset coverage under insertion/removal.

## CS61B connections

The balance table is a **hash map**; knowing that it counts occurrences, not merely membership, is critical. The proof is an example of the **sliding-window invariant** and **amortized analysis**: two nested loops need not imply quadratic time if each boundary moves monotonically and at most n times. The brute-force oracle is also a practical CS61B testing technique: use a slower independent reference to check many randomized small cases.
