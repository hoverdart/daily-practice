import unittest
from solution import min_battery_cost

class Tests(unittest.TestCase):
    def test_example(self):
        self.assertEqual(min_battery_cost(4, [(0,1,8),(1,3,8),(0,2,5),(2,3,20)]), 12)
    def test_odd_cost_floor(self):
        self.assertEqual(min_battery_cost(3, [(0,1,3),(1,2,3),(0,2,10)]), 4)
    def test_single_node(self):
        self.assertEqual(min_battery_cost(1, []), 0)
    def test_unreachable(self):
        self.assertEqual(min_battery_cost(3, [(0,1,2)]), -1)
    def test_token_changes_best_route(self):
        self.assertEqual(min_battery_cost(4, [(0,1,100),(1,3,1),(0,2,30),(2,3,30)]), 45)
    def test_parallel_edges(self):
        self.assertEqual(min_battery_cost(2, [(0,1,9),(0,1,4)]), 2)
    def test_cycle(self):
        self.assertEqual(min_battery_cost(4, [(0,1,6),(1,2,6),(2,0,1),(2,3,6)]), 4)

if __name__ == "__main__":
    unittest.main()
