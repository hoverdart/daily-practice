# Medium reference notes — Longest Consensus Segment

## Recognition signals

Look for **contiguous segment**, **change at most k elements**, **make all entries equal**, and a **maximum length** objective. This is a dynamic-frequency sliding window: a segment of length L with most common label count f needs exactly L−f edits. Unlike a sum-constrained window with negative costs, the mismatch-count structure here supports a forward-only left boundary. Numeric label order is irrelevant; a hash map handles large and negative IDs.

## Brute force versus optimal

**Brute:** For every left endpoint, extend every right endpoint, keep label frequencies, and compute the largest frequency seen in that growing segment. Check L−f ≤ k. That is O(n²) time and O(d) auxiliary space where d is the distinct-label count. A naive nested enumeration plus repeated recounting would be even slower.

**Optimal:** Use left and right pointers and a dictionary of counts in the current window. Upon including labels[right], update its frequency, and cache **max_seen_frequency**, the largest frequency encountered in the maintained windows **ever**. While window length minus that cached value exceeds k, remove labels[left] and advance left. Record the largest window length seen.

The unusual optimization is intentionally **not recomputing max_seen_frequency downward** when the dominant label leaves. Doing so by scanning all distinct keys per removal could degrade to quadratic time.

## Correctness: why can max_seen_frequency be stale?

The cached maximum never exceeds the largest frequency observed in some *earlier* window and never decreases. It can temporarily overestimate the actual most frequent label in the current physical window. Consequently, some maintained windows can be technically infeasible.

However, the algorithm asks for **only the maximum length**, not a witness window. When max_seen_frequency rises to f, a real window with f equal elements existed in the process; after its boundary adjustment there is a feasible window with the corresponding recorded length. When max_seen_frequency stays fixed, the condition length ≤ f+k prevents the algorithm from claiming a length that could not have been supported when that historical frequency f was actually realized. Any newly recorded greater length must eventually be justified by a genuinely attainable window (or matches a previously attainable maximum). Thus the reported maximum length is correct even though the current window may be stale-feasible.

Another perspective: increasing the right endpoint adds at most one to the frequency of a label; after each shrink, the window length is bounded by the historically proven f+k. This *max-length-only* argument does not authorize returning the current endpoints or label as an edit plan.

## Complexity and invariants

Each right endpoint is added once, and each left endpoint removed at most once. Hash dictionary increments, decrements, and deletions are expected O(1), so **expected O(n) time**, **O(d) extra space** (worst-case O(n)). The usual hash-table worst-case caveat applies.

The exact invariant is: **counts** reflects the physical window, **max_seen_frequency** is a nondecreasing upper bound on its actual modal frequency, and after shrinking, window length − max_seen_frequency ≤ k. Do not falsely claim the current window is necessarily feasible.

## Common mistakes

- Using a set instead of counting repeated labels.
- Assuming at most k **different values** rather than k **individual replacements**.
- Recomputing an exact maximum from the whole map during every contraction.
- Decrementing max_seen_frequency when one copy leaves, which can make it inconsistent.
- Returning a window's indices based only on the stale maximum; this answer asks for length only.
- Forgetting k=0, an empty array, all-unique labels, large negative IDs, or k≥n.
- Treating the inner while as O(n²): the left pointer only advances.

## CS61B connections

This combines hash tables, amortized pointer analysis, and a cached monotone summary. The key interview lesson is distinguishing an invariant sufficient to compute an *optimum value* from a stronger invariant needed to reconstruct a *feasible witness*. Contrast the previous signed-prefix-sum exercise, in which negative values break monotonic sum windows and require a different pattern.
