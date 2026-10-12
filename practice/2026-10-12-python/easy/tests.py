import random
import unittest
from collections import Counter

from solution import first_unique_after_each


def slow_oracle(events: list[int]) -> list[int | None]:
    answer = []
    for end in range(1, len(events) + 1):
        prefix = events[:end]
        counts = Counter(prefix)
        answer.append(next((x for x in prefix if counts[x] == 1), None))
    return answer


class Tests(unittest.TestCase):
    def test_examples(self):
        self.assertEqual(first_unique_after_each([7, 2, 7, 3, 2, 3]), [7, 7, 2, 2, 3, None])
        self.assertEqual(first_unique_after_each([4, 4, 5, 5, 6]), [4, None, 5, None, 6])
        self.assertEqual(first_unique_after_each([-2, -1, -2, -1]), [-2, -2, -1, None])

    def test_empty_and_repetition(self):
        self.assertEqual(first_unique_after_each([]), [])
        self.assertEqual(first_unique_after_each([9]), [9])
        self.assertEqual(first_unique_after_each([1, 1, 1]), [1, None, None])

    def test_does_not_mutate(self):
        values = [1, 2, 1, 3]
        original = values[:]
        first_unique_after_each(values)
        self.assertEqual(values, original)

    def test_seeded_random_oracle(self):
        rng = random.Random(20261012)
        for _ in range(200):
            values = [rng.randint(-4, 4) for _ in range(rng.randrange(0, 18))]
            with self.subTest(values=values):
                self.assertEqual(first_unique_after_each(values), slow_oracle(values))

    def test_large_stream(self):
        n = 100_000
        result = first_unique_after_each([5] * n)
        self.assertEqual(len(result), n)
        self.assertEqual(result[0], 5)
        self.assertTrue(all(x is None for x in result[1:]))


if __name__ == "__main__":
    unittest.main()
