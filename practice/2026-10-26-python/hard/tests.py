from collections import deque
import random
import unittest

from solution import safest_route


def independent_oracle(n, edges, hazards, start, goal):
    """For tiny graphs: BFS from each vertex, then enumerate simple routes."""
    graph = [[] for _ in range(n)]
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)

    safety = []
    for source in range(n):
        distance = [-1] * n
        distance[source] = 0
        queue = deque([source])
        while queue:
            u = queue.popleft()
            for v in graph[u]:
                if distance[v] == -1:
                    distance[v] = distance[u] + 1
                    queue.append(v)
        safety.append(min((distance[h] for h in hazards if distance[h] >= 0), default=n))

    best = -1

    def dfs(u, visited, score):
        nonlocal best
        if u == goal:
            best = max(best, score)
            return
        for v in graph[u]:
            if not (visited >> v) & 1:
                dfs(v, visited | (1 << v), min(score, safety[v]))

    dfs(start, 1 << start, safety[start])
    return best


class SafestRouteTests(unittest.TestCase):
    def test_examples_and_edges(self):
        cases = [
            (5, [(0, 1), (1, 2), (2, 3), (3, 4)], [0], 1, 4, 1),
            (6, [(0, 1), (1, 4), (4, 5), (0, 2), (2, 3), (3, 5)], [4], 0, 5, 1),
            (5, [(0, 1), (1, 2), (3, 4)], [4], 0, 2, 5),
            (3, [(0, 1)], [1], 0, 2, -1),
            (1, [], [0], 0, 0, 0),
            (1, [], [], 0, 0, 1),
            (3, [(0, 1), (1, 2)], [], 0, 2, 3),
            (5, [(0, 1), (1, 2), (2, 3), (3, 4)], [2], 0, 4, 0),
            (4, [(0, 1), (2, 3)], [3], 0, 1, 4),
        ]
        for n, edges, hazards, start, goal, expected in cases:
            with self.subTest(n=n, edges=edges, hazards=hazards, start=start, goal=goal):
                self.assertEqual(safest_route(n, edges, hazards, start, goal), expected)

    def test_inputs_unchanged(self):
        edges, hazards = [(0, 1), (1, 2)], [2]
        before = edges[:], hazards[:]
        safest_route(3, edges, hazards, 0, 2)
        self.assertEqual((edges, hazards), before)

    def test_seeded_independent_oracle(self):
        rng = random.Random(20261026)
        for _ in range(550):
            n = rng.randrange(1, 9)
            edges = [
                (u, v)
                for u in range(n)
                for v in range(u + 1, n)
                if rng.random() < 0.32
            ]
            hazards = [u for u in range(n) if rng.random() < 0.3]
            start, goal = rng.randrange(n), rng.randrange(n)
            self.assertEqual(
                safest_route(n, edges, hazards, start, goal),
                independent_oracle(n, edges, hazards, start, goal),
            )

    def test_large_chain(self):
        n = 80_000
        edges = [(i, i + 1) for i in range(n - 1)]
        self.assertEqual(safest_route(n, edges, [], 0, n - 1), n)
        self.assertEqual(safest_route(n, edges, [0], 1, n - 1), 1)
        self.assertEqual(safest_route(n, edges, [n // 2], 0, n - 1), 0)


if __name__ == "__main__":
    unittest.main()
