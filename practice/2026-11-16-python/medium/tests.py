"""Unittest suite with an independent exact-frequency oracle."""
import random
import unittest
from solution import longest_consensus_segment


def oracle(labels, k):
    best = 0
    for start in range(len(labels)):
        freq = {}
        max_freq = 0
        for end in range(start, len(labels)):
            value = labels[end]
            freq[value] = freq.get(value, 0) + 1
            max_freq = max(max_freq, freq[value])
            length = end - start + 1
            if length - max_freq <= k:
                best = max(best, length)
    return best


class TestConsensus(unittest.TestCase):
    def test_examples_and_edges(self):
        cases = [
            ([], 0, 0),
            ([5], 0, 1),
            ([7, 3, 7, 7, 3, 3, 7], 1, 4),
            ([1, 2, 1, 2, 1, 2], 2, 5),
            ([1, 2, 3, 4], 1, 2),
            ([4, 4, 4], 0, 3),
            ([1, 2, 3, 4], 4, 4),
            ([2, 2, 1, 2, 2, 1, 1, 1], 1, oracle([2, 2, 1, 2, 2, 1, 1, 1], 1)),
            ([-9, -9, 4, -9], 0, 2),
            ([0, 1, 0, 1, 0], 1, 3),
            ([10**9, -10**9, 10**9], 1, 3),
        ]
        for labels, k, expected in cases:
            with self.subTest(labels=labels, k=k):
                before = labels[:]
                self.assertEqual(longest_consensus_segment(labels, k), expected)
                self.assertEqual(labels, before)

    def test_seeded_random_against_exact_oracle(self):
        rng = random.Random(20261116 ^ 0x51D1)
        for _ in range(1450):
            n = rng.randrange(17)
            labels = [rng.randrange(-4, 6) for _ in range(n)]
            k = rng.randrange(n + 1)
            self.assertEqual(
                longest_consensus_segment(labels, k),
                oracle(labels, k),
                (labels, k),
            )

    def test_large_stress(self):
        n = 160_000
        alternating = [i & 1 for i in range(n)]
        self.assertEqual(longest_consensus_segment(alternating, 0), 1)
        self.assertEqual(longest_consensus_segment(alternating, n // 2), n)
        self.assertEqual(longest_consensus_segment([42] * n, 0), n)
        self.assertEqual(longest_consensus_segment(list(range(n)), 7), 8)


if __name__ == "__main__":
    unittest.main(verbosity=2)
