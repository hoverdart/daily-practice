import heapq
import random
import unittest

from solution import min_direction_overrides

DIRS = ((-1, 0), (0, 1), (1, 0), (0, -1))


def independent_dijkstra(grid):
    """Independent heap-based shortest path oracle (not deque-based)."""
    if not grid or not grid[0]:
        return 0
    rows, cols = len(grid), len(grid[0])
    dist = [[float("inf")] * cols for _ in range(rows)]
    dist[0][0] = 0
    heap = [(0, 0, 0)]
    while heap:
        cost, r, c = heapq.heappop(heap)
        if cost != dist[r][c]:
            continue
        if (r, c) == (rows - 1, cols - 1):
            return cost
        for direction, (dr, dc) in enumerate(DIRS):
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols:
                new_cost = cost + (direction != grid[r][c])
                if new_cost < dist[nr][nc]:
                    dist[nr][nc] = new_cost
                    heapq.heappush(heap, (new_cost, nr, nc))
    return -1


class RailRepairTests(unittest.TestCase):
    def test_fixed_cases(self):
        cases = [
            ([], 0),
            ([[1]], 0),
            ([[1, 1, 2], [3, 2, 2], [1, 1, 1]], 0),
            ([[1, 1, 1], [1, 1, 1]], 1),
            ([[0, 0, 0], [0, 0, 0], [0, 0, 0]], 4),
            ([[2], [2], [2], [2]], 0),
            ([[1, 1, 1, 1]], 0),
            ([[3, 3, 3, 3]], 3),
            ([[2, 3], [1, 0]], 0),
            ([[0, 2, 2], [0, 0, 2], [1, 1, 1]], 2),
        ]
        for grid, expected in cases:
            with self.subTest(grid=grid):
                self.assertEqual(min_direction_overrides(grid), expected)

    def test_no_mutation(self):
        grid = [[1, 2, 3], [0, 1, 2]]
        before = [row[:] for row in grid]
        min_direction_overrides(grid)
        self.assertEqual(grid, before)

    def test_seeded_dijkstra_oracle(self):
        rng = random.Random(20261102)
        for _ in range(1_200):
            rows = rng.randrange(1, 9)
            cols = rng.randrange(1, 9)
            grid = [[rng.randrange(4) for _ in range(cols)] for _ in range(rows)]
            self.assertEqual(min_direction_overrides(grid), independent_dijkstra(grid))

    def test_large_deque_stress(self):
        rows, cols = 250, 250
        self.assertEqual(min_direction_overrides([[1] * cols for _ in range(rows)]), rows - 1)
        self.assertEqual(min_direction_overrides([[2] * cols for _ in range(rows)]), cols - 1)
        self.assertEqual(min_direction_overrides([[1] * 100_000]), 0)
        self.assertEqual(min_direction_overrides([[2] for _ in range(100_000)]), 0)


if __name__ == "__main__":
    unittest.main()
