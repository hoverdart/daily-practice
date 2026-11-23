"""Tests against a small independent walk-over-(room,visited-mask) oracle."""
from collections import deque
import random
import unittest
from solution import max_collectible_value


def oracle(rewards, edges, start, target):
    # Enumerate reachable (current room, set of rooms already collected) states.
    # Repeated rooms don't change the mask, so states are finite despite cycles.
    n = len(rewards)
    graph = [[] for _ in range(n)]
    for u, v in edges:
        graph[u].append(v)
    initial = (start, 1 << start)
    seen = {initial}
    queue = deque([initial])
    best = -1
    while queue:
        u, mask = queue.popleft()
        if u == target:
            reward = sum(rewards[i] for i in range(n) if mask & (1 << i))
            best = max(best, reward)
        for v in graph[u]:
            state = (v, mask | (1 << v))
            if state not in seen:
                seen.add(state)
                queue.append(state)
    return best


class TestMaxUniqueRewards(unittest.TestCase):
    def test_examples_and_boundaries(self):
        cases = [
            ([2, 3, 5, 7], [(0, 1), (1, 2), (2, 1), (2, 3)], 0, 3, 17),
            ([1, 100, 4, 3], [(0, 1), (0, 2), (2, 3)], 0, 3, 8),
            ([5, 6], [(0, 1)], 1, 0, -1),
            ([10, 20], [(0, 1), (1, 0)], 0, 0, 30),
            ([0], [], 0, 0, 0),
            ([3], [(0, 0), (0, 0)], 0, 0, 3),
            ([7, 2, 1], [], 0, 2, -1),
            ([0, 0, 0], [(0, 1), (1, 2), (2, 0)], 0, 2, 0),
            ([4, 5, 6], [(0, 1), (0, 1), (1, 2), (1, 1)], 0, 2, 15),
            ([5, 1, 20, 3], [(0, 1), (1, 2), (2, 1), (1, 3)], 0, 3, 29),
            ([2, 100, 3], [(0, 1), (0, 2), (2, 0)], 0, 0, 5),
        ]
        for rewards, edges, start, target, expected in cases:
            with self.subTest(rewards=rewards, edges=edges, start=start, target=target):
                old_r, old_e = rewards[:], edges[:]
                self.assertEqual(max_collectible_value(rewards, edges, start, target), expected)
                self.assertEqual(rewards, old_r)
                self.assertEqual(edges, old_e)

    def test_random_independent_walk_oracle(self):
        rng = random.Random(20261123 ^ 0x5CC)
        for _ in range(850):
            n = rng.randrange(1, 9)
            values = [rng.randrange(0, 13) for _ in range(n)]
            edges = [(rng.randrange(n), rng.randrange(n)) for _ in range(rng.randrange(0, 25))]
            source = rng.randrange(n)
            target = rng.randrange(n)
            got = max_collectible_value(values, edges, source, target)
            expected = oracle(values, edges, source, target)
            self.assertEqual(got, expected, (values, edges, source, target))

    def test_deep_chain_and_single_scc(self):
        n = 105_000
        chain = [(i, i + 1) for i in range(n - 1)]
        values = [1] * n
        self.assertEqual(max_collectible_value(values, chain, 0, n - 1), n)
        self.assertEqual(max_collectible_value(values, chain, n - 1, 0), -1)
        ring = chain + [(n - 1, 0)]
        self.assertEqual(max_collectible_value(values, ring, n // 2, n // 2), n)

    def test_branch_that_cannot_return(self):
        n = 70_000
        values = [1] * n
        edges = [(0, 1), (1, 2)] + [(3, i) for i in range(4, n)]
        self.assertEqual(max_collectible_value(values, edges, 0, 2), 3)
        self.assertEqual(max_collectible_value(values, edges, 0, 3), -1)


if __name__ == '__main__':
    unittest.main(verbosity=2)
