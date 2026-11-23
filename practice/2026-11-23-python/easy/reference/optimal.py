"""Reference: linear multi-source BFS over an undirected graph."""
from collections import deque


def nearest_repair_hops(n: int, links: list[tuple[int, int]], hubs: list[int]) -> list[int]:
    graph = [[] for _ in range(n)]
    for u, v in links:
        graph[u].append(v)
        graph[v].append(u)

    distance = [-1] * n
    queue = deque()
    for hub in hubs:
        if distance[hub] == -1:
            distance[hub] = 0
            queue.append(hub)

    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if distance[v] == -1:
                distance[v] = distance[u] + 1
                queue.append(v)

    return distance
