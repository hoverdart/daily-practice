import random
import unittest

from solution import count_exactly_k


def slow_oracle(events: list[int], k: int) -> int:
    total = 0
    for start in range(len(events)):
        distinct = set()
        for end in range(start, len(events)):
            distinct.add(events[end])
            if len(distinct) == k:
                total += 1
    return total


class Tests(unittest.TestCase):
    def test_examples(self):
        self.assertEqual(count_exactly_k([1, 2, 1, 2, 3], 2), 7)
        self.assertEqual(count_exactly_k([1, 1, 1], 1), 6)
        self.assertEqual(count_exactly_k([1, 2, 3], 2), 2)
        self.assertEqual(count_exactly_k([-1, -2, -1], 2), 3)

    def test_boundaries(self):
        self.assertEqual(count_exactly_k([], 1), 0)
        self.assertEqual(count_exactly_k([1, 2], 0), 0)
        self.assertEqual(count_exactly_k([1, 2], 3), 0)
        self.assertEqual(count_exactly_k([9], 1), 1)
        self.assertEqual(count_exactly_k([9], 2), 0)

    def test_does_not_mutate(self):
        events = [3, 1, 3]
        before = events[:]
        count_exactly_k(events, 2)
        self.assertEqual(events, before)

    def test_seeded_random_oracle(self):
        rng = random.Random(20261013)
        for _ in range(250):
            events = [rng.randint(-3, 3) for _ in range(rng.randrange(0, 14))]
            for k in range(0, 6):
                with self.subTest(events=events, k=k):
                    self.assertEqual(count_exactly_k(events, k), slow_oracle(events, k))

    def test_large_all_equal(self):
        n = 200_000
        self.assertEqual(count_exactly_k([42] * n, 1), n * (n + 1) // 2)
        self.assertEqual(count_exactly_k([42] * n, 2), 0)


if __name__ == "__main__":
    unittest.main()
