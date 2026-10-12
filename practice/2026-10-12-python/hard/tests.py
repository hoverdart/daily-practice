import random
import unittest

from solution import earliest_arrival


def slow_time_expanded_oracle(n, routes, source, target, horizon=100):
    """Independent bounded-time reachability DP for small random graphs.

    At time t, one may wait to t+1 or take any route departing exactly at t.
    Randomized cases have a guaranteed sufficient horizon of 100.
    """
    reachable = [set() for _ in range(horizon + 1)]
    reachable[0].add(source)
    for t in range(horizon + 1):
        if target in reachable[t]:
            return t
        for u in tuple(reachable[t]):
            if t < horizon:
                reachable[t + 1].add(u)
            for a, b, first, period, travel in routes:
                if a == u and t >= first and (t - first) % period == 0 and t + travel <= horizon:
                    reachable[t + travel].add(b)
    return -1


class Tests(unittest.TestCase):
    def test_examples(self):
        self.assertEqual(earliest_arrival(4, [
            (0, 1, 0, 5, 3), (1, 3, 8, 5, 2),
            (0, 2, 0, 1, 5), (2, 3, 5, 1, 6),
        ], 0, 3), 10)
        self.assertEqual(earliest_arrival(3, [
            (0, 1, 4, 10, 2), (1, 2, 0, 3, 1), (0, 2, 0, 1, 9),
        ], 0, 2), 7)

    def test_trivial_and_unreachable(self):
        self.assertEqual(earliest_arrival(1, [], 0, 0), 0)
        self.assertEqual(earliest_arrival(3, [(0, 1, 0, 1, 2)], 0, 2), -1)
        self.assertEqual(earliest_arrival(2, [(1, 0, 0, 1, 1)], 0, 1), -1)

    def test_waiting_and_parallel_routes(self):
        self.assertEqual(earliest_arrival(2, [
            (0, 1, 0, 1, 100), (0, 1, 4, 10, 1),
        ], 0, 1), 5)
        self.assertEqual(earliest_arrival(3, [
            (0, 1, 0, 10, 3), (1, 2, 2, 10, 1), (0, 2, 0, 1, 20),
        ], 0, 2), 13)

    def test_large_time_and_large_chain(self):
        self.assertEqual(earliest_arrival(2, [
            (0, 1, 10**12, 1, 10**12),
        ], 0, 1), 2 * 10**12)
        n = 3000
        chain = [(i, i + 1, 0, 1, 1) for i in range(n - 1)]
        self.assertEqual(earliest_arrival(n, chain, 0, n - 1), n - 1)

    def test_does_not_mutate(self):
        routes = [(0, 1, 1, 2, 3)]
        before = routes[:]
        earliest_arrival(2, routes, 0, 1)
        self.assertEqual(routes, before)

    def test_seeded_random_oracle(self):
        rng = random.Random(20261014)
        for _ in range(200):
            n = rng.randrange(1, 7)
            routes = [
                (rng.randrange(n), rng.randrange(n), rng.randrange(0, 7),
                 rng.randrange(1, 6), rng.randrange(1, 6))
                for _ in range(rng.randrange(0, 15))
            ]
            source, target = rng.randrange(n), rng.randrange(n)
            with self.subTest(n=n, routes=routes, source=source, target=target):
                self.assertEqual(
                    earliest_arrival(n, routes, source, target),
                    slow_time_expanded_oracle(n, routes, source, target),
                )


if __name__ == "__main__":
    unittest.main()
