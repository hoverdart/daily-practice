import random
import unittest

from solution import longest_policy_compliant_window


def oracle(events, caps):
    best = (0, 0)
    for left in range(len(events)):
        freq = {}
        for right in range(left, len(events)):
            x = events[right]
            freq[x] = freq.get(x, 0) + 1
            if all(count <= caps.get(k, 1) for k, count in freq.items()):
                if right + 1 - left > best[1] - best[0]:
                    best = (left, right + 1)
    return best


class PolicyWindowTests(unittest.TestCase):
    def test_examples_and_edges(self):
        cases = [
            ([], {}, (0, 0)),
            ([7, 7, 8, 7], {7: 2}, (0, 3)),
            ([1, 2, 1, 2, 1, 3, 2], {1: 2, 2: 1}, (2, 6)),
            ([4, 5, 4, 5], {}, (0, 2)),
            ([1, 1, 1], {1: 0}, (0, 0)),
            ([1, 2, 3], {2: 0}, (0, 1)),
            ([5, 5, 6, 6, 5], {5: 2, 6: 2}, (0, 4)),
            ([-1, -1, 2, -1], {-1: 2, 2: 1}, (0, 3)),
            ([9], {9: 0}, (0, 0)),
            ([9], {9: 1}, (0, 1)),
            ([1, 2, 1, 2, 3], {1: 1, 2: 1, 3: 1}, (2, 5)),
        ]
        for events, caps, expected in cases:
            with self.subTest(events=events, caps=caps):
                self.assertEqual(longest_policy_compliant_window(events, caps), expected)

    def test_no_input_mutation(self):
        events, caps = [1, 2, 1], {1: 2, 2: 0}
        before = events[:], caps.copy()
        longest_policy_compliant_window(events, caps)
        self.assertEqual((events, caps), before)

    def test_seeded_exhaustive_oracle(self):
        rng = random.Random(20261102)
        for _ in range(1_200):
            n = rng.randrange(16)
            events = [rng.randrange(-3, 4) for _ in range(n)]
            caps = {k: rng.randrange(5) for k in range(-3, 4) if rng.randrange(2)}
            self.assertEqual(longest_policy_compliant_window(events, caps), oracle(events, caps))

    def test_large_amortized_cases(self):
        n = 150_000
        self.assertEqual(longest_policy_compliant_window([5] * n, {5: 500}), (0, 500))
        self.assertEqual(longest_policy_compliant_window(list(range(n)), {}), (0, n))
        self.assertEqual(longest_policy_compliant_window([1, 2] * (n // 2), {1: 0}), (1, 2))
        self.assertEqual(longest_policy_compliant_window([1, 2] * (n // 2), {1: 3, 2: 2}), (0, 5))


if __name__ == "__main__":
    unittest.main()
