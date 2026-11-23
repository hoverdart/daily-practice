"""Independent quadratic enumeration of all subarrays for small cases."""
import random
import unittest
from solution import count_signature_windows


def oracle(a, k, length_limit):
    if k <= 0 or length_limit <= 0:
        return 0
    result = 0
    for i in range(len(a)):
        seen = set()
        for j in range(i, min(len(a), i + length_limit)):
            seen.add(a[j])
            if len(seen) == k:
                result += 1
    return result


class TestSignatureWindows(unittest.TestCase):
    def test_hand_calculated(self):
        cases = [
            ([], 2, 3, 0),
            ([1], 0, 5, 0),
            ([1], 1, 0, 0),
            ([2, 1, 2, 3], 2, 3, 4),
            ([7, 7, 7], 1, 2, 5),
            ([1, 2, 1], 2, 1, 0),
            ([-1, 2, -1], 2, 3, 3),
            ([1, 2, 3], 5, 5, 0),
            ([3, 3, 3], 1, 1, 3),
            ([1, 2, 1, 2], 2, 2, 3),
            ([0, -10**9, 0, 10**9], 3, 4, 2),
        ]
        for a, k, limit, expected in cases:
            with self.subTest(a=a, k=k, limit=limit):
                before = a[:]
                self.assertEqual(count_signature_windows(a, k, limit), expected)
                self.assertEqual(a, before)

    def test_random_independent_oracle(self):
        rng = random.Random(20261123 ^ 0x51D1)
        for _ in range(2100):
            n = rng.randrange(0, 20)
            a = [rng.randrange(-5, 6) for _ in range(n)]
            k = rng.randrange(-1, n + 3)
            limit = rng.randrange(-1, n + 4)
            self.assertEqual(count_signature_windows(a, k, limit), oracle(a, k, limit), (a, k, limit))

    def test_large_counts_and_length_limit(self):
        n = 180_000
        repeated = [19] * n
        L = 700
        expected = L * (n - L + 1) + (L - 1) * L // 2
        self.assertEqual(count_signature_windows(repeated, 1, L), expected)
        self.assertEqual(count_signature_windows(repeated, 2, L), 0)
        all_distinct = list(range(n))
        self.assertEqual(count_signature_windows(all_distinct, 2, L), n - 1)
        self.assertEqual(count_signature_windows(all_distinct, n, n), 1)


if __name__ == '__main__':
    unittest.main(verbosity=2)
