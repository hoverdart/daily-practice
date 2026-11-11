# Easy solution notes — Archive Range Count Queries

## Recognition signals

- **Already sorted**, many independent interval-count queries, and inclusive endpoints.
- The desired answer is an index difference, not an actual enumeration of matching elements.
- Duplicates make two distinct boundaries important: the first position >= low and the first position > high.

## Brute force versus optimal

**Brute force:** scan all n IDs for every query, checking low <= x <= high. Time O(nq), auxiliary space O(1) beyond the output. With n = q = 200,000, this performs up to 40 billion comparisons.

**Optimal:** binary-search those boundaries with std::lower_bound and std::upper_bound. The number of elements in the half-open index range [first, pastLast) is pastLast - first. Time O(q log(n+1)), plus O(q) time to emit answers; auxiliary memory O(1) beyond the O(q) output. For n=0, both iterators equal begin/end and the count is zero.

### Copyable C++ syntax

~~~cpp
auto first = std::lower_bound(a.begin(), a.end(), lo);  // first >= lo
auto last  = std::upper_bound(a.begin(), a.end(), hi);  // first > hi
int count = static_cast<int>(last - first);
~~~

Avoid computing high + 1 to simulate upper_bound: high could be INT_MAX and overflow.

## Correctness invariant

In a sorted array, every value < low lies before lower_bound(low). Every value <= high lies before upper_bound(high). For low <= high, exactly the positions between those two indices satisfy both inequalities. No matching occurrence is omitted, even with duplicates.

## Mistakes to anticipate

1. Using lower_bound for both endpoints loses entries equal to high.
2. Using upper_bound for both endpoints loses entries equal to low.
3. Skipping the reversed-range check can produce an invalid negative count.
4. Sorting the input unnecessarily violates the no-copy/no-mutation intent.
5. Subtracting iterators from different containers is undefined; use the same vector.

## CS61B connection and spaced repetition

This is binary search / ordered arrays from CS61B, using lower/upper boundaries instead of searching for one exact match. The lower-bound invariant is a useful foundation for later binary search on answer and ordered-tree rank queries. Practice the boundary definitions from memory before coding the medium exercise.
