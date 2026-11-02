import random
import unittest

from solution import prefix_route_counts


def oracle(routes, queries):
    return [sum(route.startswith(prefix) for route in routes) for prefix in queries]


class PrefixRouteTests(unittest.TestCase):
    def test_examples_and_boundaries(self):
        cases = [
            (["ab", "abc", "ab", "b", ""],
             ["", "a", "ab", "abc", "ac", "b"], [5, 3, 3, 1, 0, 1]),
            ([], ["", "a", "xyz"], [0, 0, 0]),
            (["", "", "a"], ["", "a", "aa"], [3, 1, 0]),
            (["x", "xy", "xyz"], ["x", "xy", "xyz", "xyzz"], [3, 2, 1, 0]),
            (["z", "z", "z"], ["z", "", "a"], [3, 3, 0]),
            (["a", "b"], [], []),
        ]
        for routes, queries, expected in cases:
            with self.subTest(routes=routes, queries=queries):
                self.assertEqual(prefix_route_counts(routes, queries), expected)

    def test_does_not_mutate(self):
        routes, queries = ["ab", "ab", "b"], ["a", ""]
        before = (routes[:], queries[:])
        prefix_route_counts(routes, queries)
        self.assertEqual((routes, queries), before)

    def test_seeded_independent_oracle(self):
        rng = random.Random(20261102)
        for _ in range(800):
            routes = [
                "".join(rng.choice("abcd") for _ in range(rng.randrange(8)))
                for _ in range(rng.randrange(24))
            ]
            queries = [
                "".join(rng.choice("abcde") for _ in range(rng.randrange(7)))
                for _ in range(rng.randrange(24))
            ]
            self.assertEqual(prefix_route_counts(routes, queries), oracle(routes, queries))

    def test_large_shared_prefixes(self):
        routes = ["abcde"] * 50_000 + ["abcfg"] * 30_000 + [""] * 20_000
        queries = ["", "a", "abc", "abcd", "abcde", "abcf", "z"] * 8_000
        expected = [100_000, 80_000, 80_000, 50_000, 50_000, 30_000, 0] * 8_000
        self.assertEqual(prefix_route_counts(routes, queries), expected)


if __name__ == "__main__":
    unittest.main()
