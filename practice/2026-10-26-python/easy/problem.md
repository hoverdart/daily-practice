# Easy — First Sufficient Cache Slot

A server keeps cache slots in **nondecreasing** order of their storage capacities. A request requiring capacity `x` can use any slot with capacity at least `x`. For each request, report the **smallest zero-based index** of a suitable slot, or `-1` if no slot works.

Implement:

~~~python
def first_sufficient_slots(capacities: list[int], requests: list[int]) -> list[int]:
    ...
~~~

### Examples

- `capacities = [1, 2, 2, 5]`, `requests = [2, 3, 0, 6]` → `[1, 3, 0, -1]`.
- `capacities = [-5, -2, -2, 7]`, `requests = [-2, -3, 8]` → `[1, 1, -1]`.
- `capacities = []`, `requests = [10]` → `[-1]`.

### Constraints

- `0 <= len(capacities), len(requests) <= 200_000`.
- Capacities are sorted nondecreasingly and may be negative or duplicated; requests may be negative.
- Do not mutate either input. Return exactly one answer per request.
- Target **O(q log(n+1))** time for `n` capacities and `q` requests, O(q) output space, and O(1) auxiliary search space.
- **Implement binary search yourself**; do not call `bisect` in your solution (tests may use it).

### Interview questions

1. What would scanning every slot for every request cost?
2. In a half-open interval `[lo, hi)`, which indices are definitely too small?
3. Why is the answer `lo` when the loop ends, even with duplicate capacities?
4. What happens when every capacity is below the request, or the list is empty?
