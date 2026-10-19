import random
import unittest
from solution import route_via_relay


def oracle(n, roads, start, goal, relays):
    inf = 10**18
    dist = [[0 if i == j else inf for j in range(n)] for i in range(n)]
    for u, v, weight in roads:
        dist[u][v] = dist[v][u] = weight
    for k in range(n):
        for i in range(n):
            for j in range(n):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    options = [(dist[start][r] + dist[r][goal], r)
               for r in relays if dist[start][r] < inf and dist[r][goal] < inf]
    return min(options) if options else (-1, -1)


def check_route(testcase, n, roads, start, goal, relays):
    result = route_via_relay(n, roads, start, goal, relays)
    testcase.assertIsInstance(result, tuple)
    testcase.assertEqual(len(result), 3)
    cost, relay, path = result
    expected_cost, expected_relay = oracle(n, roads, start, goal, relays)
    testcase.assertEqual((cost, relay), (expected_cost, expected_relay))
    if expected_cost == -1:
        testcase.assertEqual(path, [])
        return
    testcase.assertTrue(path)
    testcase.assertEqual(path[0], start)
    testcase.assertEqual(path[-1], goal)
    testcase.assertIn(relay, path)
    edges = {}
    for u, v, w in roads:
        edges[u, v] = edges[v, u] = w
    actual_cost = 0
    for u, v in zip(path, path[1:]):
        testcase.assertIn((u, v), edges)
        actual_cost += edges[u, v]
    testcase.assertEqual(actual_cost, cost)


class RelayTests(unittest.TestCase):
    def test_tie_and_example(self):
        roads = [(0, 1, 2), (1, 4, 2), (0, 2, 2), (2, 4, 2)]
        self.assertEqual(route_via_relay(5, roads, 0, 4, [2, 1]), (4, 1, [0, 1, 4]))

    def test_edge_cases(self):
        cases = [
            (3, [(0, 1, 3)], 0, 2, [1]),
            (3, [(0, 1, 2), (1, 2, 2)], 0, 0, [1]),
            (1, [], 0, 0, [0]),
            (1, [], 0, 0, []),
            (4, [(0, 1, 1), (1, 2, 1)], 0, 2, [3]),
            (4, [(0, 1, 1), (1, 2, 1)], 0, 2, [0, 0]),
            (4, [(0, 1, 1), (1, 2, 1)], 0, 2, [2]),
        ]
        for args in cases:
            with self.subTest(args=args):
                check_route(self, *args)

    def test_seeded_floyd_warshall_oracle(self):
        rng = random.Random(20261021)
        for _ in range(320):
            n = rng.randrange(2, 9)
            roads = [(i, j, rng.randrange(1, 21))
                     for i in range(n) for j in range(i + 1, n)
                     if rng.random() < 0.37]
            start, goal = rng.randrange(n), rng.randrange(n)
            relays = rng.sample(range(n), rng.randrange(n + 1))
            with self.subTest(n=n, roads=roads, start=start, goal=goal, relays=relays):
                check_route(self, n, roads, start, goal, relays)

    def test_large_chain(self):
        n = 10_000
        roads = [(i, i + 1, 1) for i in range(n - 1)]
        cost, relay, path = route_via_relay(n, roads, 0, n - 1, [9000, 2000])
        self.assertEqual((cost, relay), (n - 1, 2000))
        self.assertEqual(path, list(range(n)))


if __name__ == "__main__":
    unittest.main()

