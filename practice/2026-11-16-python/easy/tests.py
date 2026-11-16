"""Unittest suite: run with python tests.py after implementing solution.py."""
import random
import unittest
from solution import kth_highest_priority


class TestKthHighestPriority(unittest.TestCase):
    def test_examples_and_boundaries(self):
        cases = [
            ([4, 1, 9, 9, -2], 3, 4),
            ([8, 8, 8], 2, 8),
            ([-7, -1, -5], 1, -1),
            ([10, 2, 4, 6], 4, 2),
            ([3], 1, 3),
            ([5, 5, 1, 5, 1], 4, 1),
            ([-10**9, 10**9, 0], 2, 0),
            (list(range(30)), 30, 0),
        ]
        for data, k, answer in cases:
            with self.subTest(data=data, k=k):
                original = data[:]
                self.assertEqual(kth_highest_priority(data, k), answer)
                self.assertEqual(data, original, "must not mutate input")

    def test_invalid_k(self):
        for arr, k in [([], 0), ([2, 3], 0), ([1], 2), ([7, 8], -1)]:
            with self.subTest(arr=arr, k=k):
                with self.assertRaises(ValueError):
                    kth_highest_priority(arr, k)

    def test_seeded_independent_oracle(self):
        rng = random.Random(20261116)
        for _ in range(1300):
            n = rng.randint(1, 38)
            values = [rng.randint(-12, 12) for _ in range(n)]
            k = rng.randint(1, n)
            answer = sorted(values, reverse=True)[k - 1]
            before = values[:]
            self.assertEqual(kth_highest_priority(values, k), answer, (values, k))
            self.assertEqual(values, before)

    def test_large_stress(self):
        n = 150_000
        self.assertEqual(kth_highest_priority(list(range(n)), 37), n - 37)
        self.assertEqual(kth_highest_priority(list(range(n - 1, -1, -1)), 37), n - 37)
        self.assertEqual(kth_highest_priority([-4] * n, 77_777), -4)


if __name__ == "__main__":
    unittest.main(verbosity=2)
