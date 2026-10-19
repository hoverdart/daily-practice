import random
import unittest
from solution import count_light_batches


def brute(loads: list[int], limit: int) -> int:
    total = 0
    for left in range(len(loads)):
        product = 1
        for right in range(left, len(loads)):
            product *= loads[right]
            if product < limit:
                total += 1
    return total


class LowLoadTests(unittest.TestCase):
    def test_examples_and_boundaries(self):
        cases = [
            ([10, 5, 2, 6], 100, 8),
            ([1, 1, 1], 2, 6),
            ([4, 4, 4], 16, 3),
            ([1, 2, 3], 1, 0),
            ([1, 2, 3], 0, 0),
            ([], 100, 0),
            ([100], 100, 0),
            ([100], 101, 1),
            ([2, 3, 4], 7, 4),
            ([1], -5, 0),
        ]
        for values, limit, expected in cases:
            with self.subTest(values=values, limit=limit):
                self.assertEqual(count_light_batches(values, limit), expected)

    def test_seeded_oracle(self):
        rng = random.Random(20261020)
        for _ in range(500):
            values = [rng.randint(1, 9) for _ in range(rng.randrange(18))]
            limit = rng.randint(-3, 120)
            with self.subTest(values=values, limit=limit):
                self.assertEqual(count_light_batches(values, limit), brute(values, limit))

    def test_input_unchanged(self):
        values = [10, 5, 2, 6]
        count_light_batches(values, 100)
        self.assertEqual(values, [10, 5, 2, 6])

    def test_large_all_ones(self):
        n = 100_000
        self.assertEqual(count_light_batches([1] * n, 2), n * (n + 1) // 2)


if __name__ == "__main__":
    unittest.main()

