import heapq

def min_battery_cost(n: int, edges: list[tuple[int, int, int]]) -> int:
    graph = [[] for _ in range(n)]
    for u, v, cost in edges:
        graph[u].append((v, cost))
        graph[v].append((u, cost))
    inf = float("inf")
    dist = [[inf, inf] for _ in range(n)]
    dist[0][0] = 0
    pq = [(0, 0, 0)]
    while pq:
        cost_so_far, node, used = heapq.heappop(pq)
        if cost_so_far != dist[node][used]:
            continue
        if node == n - 1:
            return cost_so_far
        for nxt, weight in graph[node]:
            normal = cost_so_far + weight
            if normal < dist[nxt][used]:
                dist[nxt][used] = normal
                heapq.heappush(pq, (normal, nxt, used))
            if used == 0:
                discounted = cost_so_far + weight // 2
                if discounted < dist[nxt][1]:
                    dist[nxt][1] = discounted
                    heapq.heappush(pq, (discounted, nxt, 1))
    return -1
