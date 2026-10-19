import heapq


def route_via_relay(
    n: int,
    roads: list[tuple[int, int, int]],
    start: int,
    goal: int,
    relays: list[int],
) -> tuple[int, int, list[int]]:
    graph: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    for u, v, weight in roads:
        graph[u].append((v, weight))
        graph[v].append((u, weight))

    def dijkstra(source: int) -> tuple[list[float], list[int]]:
        distance = [float("inf")] * n
        parent = [-1] * n
        distance[source] = 0
        heap = [(0, source)]
        while heap:
            cost, u = heapq.heappop(heap)
            if cost != distance[u]:
                continue
            for v, weight in graph[u]:
                candidate = cost + weight
                if candidate < distance[v]:
                    distance[v] = candidate
                    parent[v] = u
                    heapq.heappush(heap, (candidate, v))
        return distance, parent

    from_start, start_parent = dijkstra(start)
    from_goal, goal_parent = dijkstra(goal)

    choices = [
        (from_start[r] + from_goal[r], r)
        for r in relays
        if from_start[r] != float("inf") and from_goal[r] != float("inf")
    ]
    if not choices:
        return (-1, -1, [])

    cost, relay = min(choices)  # (distance, relay ID) tie-breaking
    first_half = []
    node = relay
    while node != -1:
        first_half.append(node)
        node = start_parent[node]
    first_half.reverse()  # start -> relay

    route = first_half
    node = relay
    while node != goal:
        node = goal_parent[node]  # follow goal-rooted tree toward goal
        route.append(node)        # append next vertex, not relay again
    return (cost, relay, route)

