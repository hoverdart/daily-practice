"""Run 'python tests.py' after implementing solution.py."""
from collections import deque
import random
import unittest
from solution import nearest_repair_hops


def independent_oracle(n, links, hubs):
    # Different algorithm: BFS separately from every vertex, searching for a hub.
    adj = [[] for _ in range(n)]
    for u, v in links:
        adj[u].append(v)
        adj[v].append(u)
    targets = set(hubs)
    answers = []
    for src in range(n):
        q = deque([(src, 0)])
        visited = {src}
        result = -1
        while q:
            u, d = q.popleft()
            if u in targets:
                result = d
                break
            for v in adj[u]:
                if v not in visited:
                    visited.add(v)
                    q.append((v, d + 1))
        answers.append(result)
    return answers


class TestNearestRepairHops(unittest.TestCase):
    def test_hand_checked(self):
        cases = [
            (0, [], [], []),
            (1, [], [], [-1]),
            (1, [(0, 0)], [0, 0], [0]),
            (6, [(0, 1), (1, 2), (2, 3), (4, 5)], [0, 5], [0, 1, 2, 3, 1, 0]),
            (4, [(0, 1), (2, 3)], [], [-1, -1, -1, -1]),
            (5, [(0, 1), (1, 2), (2, 3), (3, 4)], [0, 4], [0, 1, 2, 1, 0]),
            (4, [(0, 1), (1, 0), (2, 2)], [1, 1], [1, 0, -1, -1]),
            (4, [(0, 1), (1, 2), (2, 3)], [1, 2], [1, 0, 0, 1]),
        ]
        for n, links, hubs, expected in cases:
            with self.subTest(n=n, links=links, hubs=hubs):
                a, b = links[:], hubs[:]
                self.assertEqual(nearest_repair_hops(n, links, hubs), expected)
                self.assertEqual(links, a)
                self.assertEqual(hubs, b)

    def test_seeded_random_against_independent_oracle(self):
        rng = random.Random(20261123)
        for _ in range(1050):
            n = rng.randrange(0, 13)
            edges = [(rng.randrange(n), rng.randrange(n)) for _ in range(rng.randrange(30))] if n else []
            hubs = [rng.randrange(n) for _ in range(rng.randrange(n + 2))] if n else []
            self.assertEqual(nearest_repair_hops(n, edges, hubs), independent_oracle(n, edges, hubs), (n, edges, hubs))

    def test_large_disconnected_stress(self):
        n = 120_000
        edges = [(i, i + 1) for i in range(n - 2)]
        answer = nearest_repair_hops(n, edges, [0, 0, n - 1])
        self.assertEqual(len(answer), n)
        self.assertEqual(answer[0], 0)
        self.assertEqual(answer[17], 17)
        self.assertEqual(answer[-2], n - 2)
        self.assertEqual(answer[-1], 0)
        self.assertEqual(nearest_repair_hops(n, [], []), [-1] * n)


if __name__ == '__main__':
    unittest.main(verbosity=2)
