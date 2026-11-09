"""Run from this folder with: python tests.py"""
from __future__ import annotations

import random
from collections import Counter
from solution import smallest_complete_snapshot


def oracle(events, required):
    """Independent exhaustive enumeration, O(n^2*u) on small inputs."""
    if not required:
        return (0, 0)
    answer = (-1, -1)
    n = len(events)
    for left in range(n):
        counts = Counter()
        for right in range(left, n):
            counts[events[right]] += 1
            if all(counts[x] >= amount for x, amount in required.items()):
                candidate = (left, right + 1)
                if (answer == (-1, -1)
                    or (candidate[1] - candidate[0], candidate[0])
                    < (answer[1] - answer[0], answer[0])):
                    answer = candidate
                break  # longer endpoints for same left cannot win
    return answer


fixed = [
    ([], {}, (0, 0)),
    ([], {1: 1}, (-1, -1)),
    ([1, 2, 3], {}, (0, 0)),
    ([8, 5, 8, 7, 5, 8, 7], {8: 2, 5: 1}, (0, 3)),
    ([3, 2, 1, 2, 3], {2: 1, 3: 1}, (0, 2)),
    ([4, 2, 2, 5, 4, 2], {2: 2, 4: 1}, (0, 3)),
    ([9, 9, 2, 3], {2: 1, 3: 1}, (2, 4)),
    ([1, 1, 1], {1: 4}, (-1, -1)),
    ([-4, -2, -4, -2], {-4: 2, -2: 1}, (0, 3)),
    ([5, 6, 7], {5: 1, 6: 1, 7: 1, 10: 1}, (-1, -1)),
    ([6, 6, 6], {6: 1}, (0, 1)),
]
for events, request, expected in fixed:
    before_events, before_request = events[:], request.copy()
    got = smallest_complete_snapshot(events, request)
    assert got == expected, (events, request, got, expected)
    assert events == before_events and request == before_request

rng = random.Random(20261109)
for trial in range(1500):
    n = rng.randint(0, 23)
    events = [rng.randint(-4, 4) for _ in range(n)]
    required = {}
    for value in range(-4, 5):
        if rng.randrange(4) == 0:
            required[value] = rng.randint(1, 5)
    exp = oracle(events, required)
    events_before, req_before = events[:], required.copy()
    got = smallest_complete_snapshot(events, required)
    assert got == exp, (trial, events, required, got, exp)
    assert events == events_before and required == req_before

# Large input: the unique shortest qualifying interval uses the last 50k
# ones and first 50k twos.
large = [1] * 100000 + [2] * 100000
request = {1: 50000, 2: 50000}
assert smallest_complete_snapshot(large, request) == (50000, 150000)
assert smallest_complete_snapshot(large, {3: 1}) == (-1, -1)
assert smallest_complete_snapshot(large, {}) == (0, 0)
print("PASS medium: fixed, 1500 seeded brute-force comparisons, 200k stress")
