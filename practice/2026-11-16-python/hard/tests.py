"""Tests: brute-force independent traversals plus deep-tree stress."""
import random
import unittest
from solution import farthest_critical_distances


def oracle(n, edges, critical):
    graph = [[] for _ in range(n)]
    for a, b, w in edges:
        graph[a].append((b, w))
        graph[b].append((a, w))
    ans = [-1] * n
    for start in set(critical):
        distances = [-1] * n
        distances[start] = 0
        order = [start]
        for u in order:
            for v, w in graph[u]:
                if distances[v] == -1:
                    distances[v] = distances[u] + w
                    order.append(v)
        for u in range(n):
            ans[u] = max(ans[u], distances[u])
    return ans


class TestFarthestCritical(unittest.TestCase):
    def test_examples_and_corner_cases(self):
        cases = [
            (1, [], [], [-1]),
            (1, [], [0], [0]),
            (2, [(0, 1, 9)], [], [-1, -1]),
            (3, [(0, 1, 1), (1, 2, 8)], [1], [1, 0, 8]),
            (4, [(0, 1, 2), (1, 2, 3), (1, 3, 4)], [0, 2], [5, 3, 5, 7]),
            (3, [(0, 1, 0), (1, 2, 0)], [0, 2, 2], [0, 0, 0]),
            (4, [(0, 1, 3), (0, 2, 3), (0, 3, 3)], [1, 2], [3, 6, 6, 6]),
            (3, [(0, 1, 10**6), (1, 2, 10**6)], [0, 2], [2*10**6, 10**6, 2*10**6]),
        ]
        for n, edges, marked, expected in cases:
            with self.subTest(n=n, edges=edges, critical=marked):
                original_edges = edges[:]
                original_marked = marked[:]
                self.assertEqual(farthest_critical_distances(n, edges, marked), expected)
                self.assertEqual(edges, original_edges)
                self.assertEqual(marked, original_marked)

    def test_seeded_independent_oracle(self):
        rng = random.Random(20261116 ^ 0xF0E5)
        for _ in range(1100):
            n = rng.randint(1, 16)
            edges = [(v, rng.randrange(v), rng.randrange(11)) for v in range(1, n)]
            rng.shuffle(edges)
            marked = [i for i in range(n) if rng.randrange(4) == 0]
            if marked and rng.randrange(4) == 0:
                marked.append(rng.choice(marked))
            answer = oracle(n, edges, marked)
            self.assertEqual(
                farthest_critical_distances(n, edges, marked),
                answer, (n, edges, marked),
            )

    def test_deep_chain_without_recursion(self):
        n = 120_000
        edges = [(i, i + 1, 1) for i in range(n - 1)]
        got = farthest_critical_distances(n, edges, [0, n - 1])
        self.assertEqual(len(got), n)
        for i in [0, 1, 17, n // 2, n - 2, n - 1]:
            self.assertEqual(got[i], max(i, n - 1 - i))

    def test_star_and_empty_marks(self):
        n = 100_000
        edges = [(0, i, 3) for i in range(1, n)]
        got = farthest_critical_distances(n, edges, [1, 1])
        self.assertEqual(got[:5], [3, 0, 6, 6, 6])
        self.assertEqual(got[-1], 6)
        self.assertEqual(farthest_critical_distances(3, [(0, 1, 1), (1, 2, 2)], []),
                         [-1, -1, -1])


if __name__ == "__main__":
    unittest.main(verbosity=2)
