import bisect
import random
import unittest

from solution import first_sufficient_slots


def oracle(capacities: list[int], requests: list[int]) -> list[int]:
    return [
        i if (i := bisect.bisect_left(capacities, target)) < len(capacities) else -1
        for target in requests
    ]


class CacheSlotTests(unittest.TestCase):
    def test_examples_and_boundaries(self):
        cases = [
            ([], [], []),
            ([], [10], [-1]),
            ([1, 2, 2, 5], [2, 3, 0, 6], [1, 3, 0, -1]),
            ([-5, -2, -2, 7], [-2, -3, 8], [1, 1, -1]),
            ([4, 4, 4], [4, 5, 3], [0, -1, 0]),
            ([1, 2, 3], [], []),
            ([9], [8, 9, 10], [0, 0, -1]),
        ]
        for capacities, requests, expected in cases:
            with self.subTest(capacities=capacities, requests=requests):
                self.assertEqual(first_sufficient_slots(capacities, requests), expected)

    def test_inputs_unchanged(self):
        capacities, requests = [-3, -3, 0, 8], [0, 8, 10]
        before = capacities[:], requests[:]
        first_sufficient_slots(capacities, requests)
        self.assertEqual((capacities, requests), before)

    def test_seeded_oracle(self):
        rng = random.Random(20261026)
        for _ in range(600):
            capacities = sorted(rng.randint(-20, 20) for _ in range(rng.randrange(30)))
            requests = [rng.randint(-25, 25) for _ in range(rng.randrange(24))]
            self.assertEqual(first_sufficient_slots(capacities, requests), oracle(capacities, requests))

    def test_large_many_duplicates(self):
        capacities = [i // 3 for i in range(120_000)]
        requests = [-1, 0, 1, 39_999, 40_000] * 20_000
        expected = [0, 0, 3, 119_997, -1] * 20_000
        self.assertEqual(first_sufficient_slots(capacities, requests), expected)


if __name__ == "__main__":
    unittest.main()
