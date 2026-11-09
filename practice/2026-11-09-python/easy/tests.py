"""Run from this folder with: python tests.py"""
from __future__ import annotations

import copy
import random
from solution import merge_service_windows


def oracle(windows):
    """Independent O(n^2) connected-components oracle on *original* overlaps."""
    n = len(windows)
    parent = list(range(n))

    def root(x):
        while parent[x] != x:
            x = parent[x]
        return x

    for i in range(n):
        for j in range(i):
            a, b = windows[i], windows[j]
            if max(a[0], b[0]) <= min(a[1], b[1]):
                parent[root(i)] = root(j)

    components = {}
    for i, (start, end) in enumerate(windows):
        key = root(i)
        if key not in components:
            components[key] = [start, end]
        else:
            components[key][0] = min(components[key][0], start)
            components[key][1] = max(components[key][1], end)
    return sorted(components.values())


fixed = [
    ([], []),
    ([[2, 7]], [[2, 7]]),
    ([[4, 5], [1, 4]], [[1, 5]]),
    ([[8, 10], [1, 4], [3, 6], [6, 9], [15, 17]], [[1, 10], [15, 17]]),
    ([[1, 10], [2, 3], [9, 11]], [[1, 11]]),
    ([[-5, -3], [-2, 0]], [[-5, -3], [-2, 0]]),
    ([[2, 3], [2, 3], [3, 7]], [[2, 7]]),
    ([[-1000000000, -1], [0, 1000000000]], [[-1000000000, -1], [0, 1000000000]]),
]
for windows, expected in fixed:
    before = copy.deepcopy(windows)
    got = merge_service_windows(windows)
    assert got == expected, (windows, expected, got)
    assert windows == before, "The function modified the input"

rng = random.Random(20261109)
for trial in range(1000):
    n = rng.randrange(0, 17)
    windows = []
    for _ in range(n):
        a = rng.randint(-15, 15)
        windows.append([a, a + rng.randint(1, 12)])
    before = copy.deepcopy(windows)
    expected = oracle(windows)
    got = merge_service_windows(windows)
    assert got == expected, (trial, windows, expected, got)
    assert windows == before

# Large disjoint and touching inputs probe n log n vs n^2 implementations.
disjoint = [[3 * i, 3 * i + 1] for i in range(100000)]
assert merge_service_windows(disjoint) == disjoint
touching = [[i, i + 1] for i in range(200000)]
assert merge_service_windows(touching) == [[0, 200000]]
assert touching[0] == [0, 1] and touching[-1] == [199999, 200000]
print("PASS easy: fixed, 1000 seeded oracle cases, large sorting/sweep stress")
