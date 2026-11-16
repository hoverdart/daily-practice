"""Reference: O(n) iterative rooted-tree DP and a reroot/outside-subtree pass."""


def farthest_critical_distances(
    n: int, edges: list[tuple[int, int, int]], critical: list[int]
) -> list[int]:
    graph: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    for u, v, weight in edges:
        graph[u].append((v, weight))
        graph[v].append((u, weight))

    parent = [-1] * n
    parent[0] = 0
    order = [0]
    for u in order:  # Iteratively build a parent-before-child traversal.
        for v, _ in graph[u]:
            if v != parent[u]:
                parent[v] = u
                order.append(v)

    marked = set(critical)
    down = [-1] * n
    for u in reversed(order):
        if u in marked:
            down[u] = 0
        for v, weight in graph[u]:
            if parent[v] == u and down[v] >= 0:
                down[u] = max(down[u], down[v] + weight)

    up = [-1] * n
    for u in order:
        # A child source is its vertex id; -1 means "self is critical".
        best1 = (0, -1) if u in marked else (-1, -2)
        best2 = (-1, -2)
        for v, weight in graph[u]:
            if parent[v] != u or down[v] < 0:
                continue
            value = down[v] + weight
            if value >= best1[0]:
                best2 = best1
                best1 = (value, v)
            elif value > best2[0]:
                best2 = (value, v)

        for v, weight in graph[u]:
            if parent[v] != u:
                continue
            best_excluding_v = best1[0] if best1[1] != v else best2[0]
            outside_from_u = max(up[u], best_excluding_v)
            if outside_from_u >= 0:
                up[v] = outside_from_u + weight

    return [max(d, u) for d, u in zip(down, up)]
