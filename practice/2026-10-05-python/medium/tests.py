import unittest
from solution import longest_stable_window

class Tests(unittest.TestCase):
    def test_mixed(self): self.assertEqual(longest_stable_window([1, 2, 1, 2, 3], 2), 4)
    def test_all_same(self): self.assertEqual(longest_stable_window([4, 4, 4], 1), 3)
    def test_one_distinct(self): self.assertEqual(longest_stable_window([1, 2, 3], 1), 1)
    def test_empty(self): self.assertEqual(longest_stable_window([], 3), 0)
    def test_zero_k(self): self.assertEqual(longest_stable_window([1, 1], 0), 0)
    def test_shrink_multiple_steps(self): self.assertEqual(longest_stable_window([1, 2, 3, 2, 2, 1], 2), 4)
    def test_negative_codes(self): self.assertEqual(longest_stable_window([-1, -2, -1, -3, -3], 2), 3)

if __name__ == "__main__":
    unittest.main()
