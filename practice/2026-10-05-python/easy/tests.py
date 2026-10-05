import unittest
from solution import first_revisited

class Tests(unittest.TestCase):
    def test_example(self):
        self.assertEqual(first_revisited([4, 7, 2, 7, 4]), 7)
    def test_immediate_repeat(self):
        self.assertEqual(first_revisited([5, 5, 5]), 5)
    def test_unique(self):
        self.assertIsNone(first_revisited([1, 2, 3]))
    def test_empty(self):
        self.assertIsNone(first_revisited([]))
    def test_negative_and_order(self):
        self.assertEqual(first_revisited([-1, 8, -1, 8]), -1)
    def test_first_revisit_not_smallest_value(self):
        self.assertEqual(first_revisited([9, 1, 2, 2, 1]), 2)

if __name__ == "__main__":
    unittest.main()
