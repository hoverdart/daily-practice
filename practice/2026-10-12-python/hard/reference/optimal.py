from heapq import heappop, heappush


def earliest_arrival(
    n: int,
    routes: list[tuple[int, int, int, int, int]],
    source: int,
    target: int,
) -> int:
    graph: list[list[tuple[int, int, int, int]]] = [[] for _ in range(n)]
    for u, v, first, period, travel in routes:
        graph[u].append((v, first, period, travel))

    dist = [float("inf")] * n
    dist[source] = 0
    heap = [(0, source)]

    while heap:
        time, u = heappop(heap)
        if time != dist[u]:
            continue
        if u == target:
            return time

        for v, first, period, travel in graph[u]:
            if time <= first:
                departure = first
            else:
                departure = first + ((time - first + period - 1) // period) * period

            arrival = departure + travel
            if arrival < dist[v]:
                dist[v] = arrival
                heappush(heap, (arrival, v))

    return -1
