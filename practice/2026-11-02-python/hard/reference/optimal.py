from collections import deque


def min_direction_overrides(grid: list[list[int]]) -> int:
    if not grid or not grid[0]:
        return 0

    rows, cols = len(grid), len(grid[0])
    directions = ((-1, 0), (0, 1), (1, 0), (0, -1))
    infinity = rows * cols + 1
    dist = [[infinity] * cols for _ in range(rows)]
    dist[0][0] = 0
    dq = deque([(0, 0, 0)])  # (recorded distance, row, column)

    while dq:
        cost, r, c = dq.popleft()
        if cost != dist[r][c]:
            continue  # stale entry from an earlier, worse relaxation
        if (r, c) == (rows - 1, cols - 1):
            return cost

        for direction, (dr, dc) in enumerate(directions):
            nr, nc = r + dr, c + dc
            if not (0 <= nr < rows and 0 <= nc < cols):
                continue

            weight = 0 if grid[r][c] == direction else 1
            candidate = cost + weight
            if candidate < dist[nr][nc]:
                dist[nr][nc] = candidate
                state = (candidate, nr, nc)
                if weight == 0:
                    dq.appendleft(state)
                else:
                    dq.append(state)

    return -1
