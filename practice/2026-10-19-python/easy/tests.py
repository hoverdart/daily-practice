import random
import unittest
from solution import count_zero_sum_spans


def brute(values: list[int]) -> int:
    answer = 0
    for left in range(len(values)):
        running = 0
        for right in range(left, len(values)):
            running += values[right]
            if running == 0:
                answer += 1
    return answer


class ZeroBalanceTests(unittest.TestCase):
    def test_examples_and_edges(self):
        cases = [
            ([], 0), ([0], 1), ([0, 0, 0], 6),
            ([2, -2, 3, -3], 3), ([1, 2, 3], 0),
            ([1, -1, 1, -1], 4), ([-3, 3, 0], 3),
            ([10**6, -10**6], 1), ([5, -2, -3, 4], 1),
        ]
        for values, expected in cases:
            with self.subTest(values=values):
                self.assertEqual(count_zero_sum_spans(values), expected)

    def test_does_not_mutate(self):
        values = [3, -3, 2, -2]
        original = values[:]
        count_zero_sum_spans(values)
        self.assertEqual(values, original)

    def test_seeded_oracle(self):
        rng = random.Random(20261019)
        for _ in range(450):
            values = [rng.randint(-6, 6) for _ in range(rng.randrange(18))]
            with self.subTest(values=values):
                self.assertEqual(count_zero_sum_spans(values), brute(values))

    def test_large_all_zero(self):
        n = 100_000
        self.assertEqual(count_zero_sum_spans([0] * n), n * (n + 1) // 2)


if __name__ == "__main__":
    unittest.main()

