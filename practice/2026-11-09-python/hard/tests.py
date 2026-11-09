"""Run from this folder with: python tests.py"""
from __future__ import annotations

import random
from solution import minimum_coupon_route


def oracle(n, edges, source, target):
    """Independent Bellman-Ford relaxation on 2n expanded vertices."""
    inf = 10**40
    dist = [inf] * (2 * n)
    dist[source] = 0  # layer 0: coupon unused; layer 1: coupon used
    for _ in range(2 * n - 1):
        changed = False
        for u, v, w in edges:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                changed = True
            if dist[u] + w // 2 < dist[n + v]:
                dist[n + v] = dist[u] + w // 2
                changed = True
            if dist[n + u] + w < dist[n + v]:
                dist[n + v] = dist[n + u] + w
                changed = True
        if not changed:
            break
    ans = min(dist[target], dist[n + target])
    return -1 if ans == inf else ans


fixed = [
    (1, [], 0, 0, 0),
    (2, [], 0, 1, -1),
    (2, [(0, 1, 100)], 0, 1, 50),
    (2, [(1, 0, 100)], 0, 1, -1),
    (4, [(0, 1, 9), (1, 3, 7), (0, 2, 3),
         (2, 3, 20), (0, 3, 30)], 0, 3, 11),
    (3, [(0, 1, 0), (1, 2, 0)], 0, 2, 0),
    (3, [(0, 1, 7), (0, 1, 2), (1, 2, 5)], 0, 2, 4),
    (3, [(0, 0, 0), (0, 1, 8), (1, 2, 0)], 0, 2, 4),
    (2, [(0, 1, 1)], 0, 1, 0),
    (2, [(0, 1, 1000000000)], 0, 1, 500000000),
]
for n, edges, source, target, expected in fixed:
    before = edges[:]
    got = minimum_coupon_route(n, edges, source, target)
    assert got == expected, (n, edges, source, target, got, expected)
    assert edges == before

rng = random.Random(20261109)
for trial in range(1200):
    n = rng.randint(1, 8)
    m = rng.randint(0, 28)
    edges = [(rng.randrange(n), rng.randrange(n), rng.randrange(0, 41))
             for _ in range(m)]
    source, target = rng.randrange(n), rng.randrange(n)
    expected = oracle(n, edges, source, target)
    got = minimum_coupon_route(n, edges, source, target)
    assert got == expected, (trial, n, edges, source, target, got, expected)

# A long chain forces a graph algorithm rather than enumerating paths.
n = 70000
chain = [(i, i + 1, 2) for i in range(n - 1)]
assert minimum_coupon_route(n, chain, 0, n - 1) == 2 * (n - 1) - 1
assert minimum_coupon_route(n, chain, n - 1, 0) == -1
print("PASS hard: fixed, 1200 seeded Bellman-Ford oracle cases, 70k chain stress")
