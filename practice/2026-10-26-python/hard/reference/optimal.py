from collections import deque
from heapq import heappop, heappush


def safest_route(
    n: int,
    edges: list[tuple[int, int]],
    hazards: list[int],
    start: int,
    goal: int,
) -> int:
    graph: list[list[int]] = [[] for _ in range(n)]
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)

    danger_distance = [n] * n
    queue = deque()
    for h in hazards:
        danger_distance[h] = 0
        queue.append(h)
    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if danger_distance[v] == n:
                danger_distance[v] = danger_distance[u] + 1
                queue.append(v)

    best = [-1] * n
    best[start] = danger_distance[start]
    heap = [(-best[start], start)]
    while heap:
        neg_score, u = heappop(heap)
        score = -neg_score
        if score != best[u]:
            continue
        if u == goal:
            return score
        for v in graph[u]:
            candidate = min(score, danger_distance[v])
            if candidate > best[v]:
                best[v] = candidate
                heappush(heap, (-candidate, v))
    return -1
