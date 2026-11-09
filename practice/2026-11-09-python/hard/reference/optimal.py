"""Reference solution — read only after attempting hard/solution.py."""

from heapq import heappop, heappush


def minimum_coupon_route(
    n: int, edges: list[tuple[int, int, int]], source: int, target: int
) -> int:
    graph = [[] for _ in range(n)]
    for u, v, toll in edges:
        graph[u].append((v, toll))

    inf = float("inf")
    # dist[v][0] = best cost before coupon; dist[v][1] = best cost after coupon.
    dist = [[inf, inf] for _ in range(n)]
    dist[source][0] = 0
    heap = [(0, source, 0)]

    while heap:
        cost, u, used = heappop(heap)
        if cost != dist[u][used]:
            continue
        if u == target:
            return cost

        for v, w in graph[u]:
            regular = cost + w
            if regular < dist[v][used]:
                dist[v][used] = regular
                heappush(heap, (regular, v, used))

            if used == 0:
                discounted = cost + w // 2
                if discounted < dist[v][1]:
                    dist[v][1] = discounted
                    heappush(heap, (discounted, v, 1))

    return -1
