import random
import unittest

from solution import longest_affordable_window


def brute(channels, costs, max_types, budget):
    best = (0, 0)
    for left in range(len(channels)):
        types = set()
        total = 0
        for right in range(left, len(channels)):
            types.add(channels[right])
            total += costs[right]
            if len(types) <= max_types and total <= budget:
                if right + 1 - left > best[1] - best[0]:
                    best = (left, right + 1)
    return best


class AffordableWindowTests(unittest.TestCase):
    def test_examples_and_edges(self):
        cases = [
            ([], [], 0, 0, (0, 0)),
            ([1, 2, 1, 3, 1], [2, 1, 1, 1, 2], 2, 4, (0, 3)),
            ([1, 1, 2, 2, 1], [3, 1, 1, 1, 1], 2, 4, (1, 5)),
            ([9, 8, 7], [5, 5, 5], 3, 4, (0, 0)),
            ([7, 8, 7, 8], [0, 0, 0, 0], 1, 0, (0, 1)),
            ([4, 4, 4], [0, 0, 0], 1, 0, (0, 3)),
            ([1, 2, 3], [0, 0, 0], 2, 0, (0, 2)),
            ([2, 2, 2], [0, 1, 0], 0, 10, (0, 0)),
            ([5], [10**9], 1, 10**9, (0, 1)),
        ]
        for channels, costs, k, budget, expected in cases:
            with self.subTest(channels=channels, costs=costs, k=k, budget=budget):
                self.assertEqual(longest_affordable_window(channels, costs, k, budget), expected)

    def test_does_not_mutate(self):
        channels, costs = [4, 5, 4], [1, 0, 2]
        before = channels[:], costs[:]
        longest_affordable_window(channels, costs, 2, 2)
        self.assertEqual((channels, costs), before)

    def test_seeded_independent_oracle(self):
        rng = random.Random(20261026)
        for _ in range(800):
            n = rng.randrange(13)
            channels = [rng.randint(-3, 3) for _ in range(n)]
            costs = [rng.randrange(8) for _ in range(n)]
            k = rng.randrange(n + 1)
            budget = rng.randrange(22)
            self.assertEqual(
                longest_affordable_window(channels, costs, k, budget),
                brute(channels, costs, k, budget),
            )

    def test_large_amortized(self):
        n = 100_000
        self.assertEqual(
            longest_affordable_window([3] * n, [1] * n, 1, 50_000),
            (0, 50_000),
        )
        self.assertEqual(
            longest_affordable_window([1, 2] * 50_000, [0] * n, 2, 0),
            (0, n),
        )


if __name__ == "__main__":
    unittest.main()
