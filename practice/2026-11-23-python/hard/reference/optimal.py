"""Reference: iterative Kosaraju SCCs + maximum-weight condensation DAG path."""
from collections import deque


def max_collectible_value(
    rewards: list[int], edges: list[tuple[int, int]], start: int, target: int
) -> int:
    n = len(rewards)
    graph = [[] for _ in range(n)]
    reverse = [[] for _ in range(n)]
    for u, v in edges:
        graph[u].append(v)
        reverse[v].append(u)

    # First DFS pass: record *postorder*, not discovery order.
    visited = bytearray(n)
    finish = []
    for root in range(n):
        if visited[root]:
            continue
        visited[root] = 1
        stack = [(root, 0)]  # (vertex, index of next outgoing edge)
        while stack:
            u, next_index = stack[-1]
            if next_index == len(graph[u]):
                finish.append(u)
                stack.pop()
            else:
                v = graph[u][next_index]
                stack[-1] = (u, next_index + 1)
                if not visited[v]:
                    visited[v] = 1
                    stack.append((v, 0))

    # Second DFS pass on reversed edges, in reverse finishing order.
    component = [-1] * n
    component_value = []
    for root in reversed(finish):
        if component[root] != -1:
            continue
        cid = len(component_value)
        total = 0
        stack = [root]
        component[root] = cid
        while stack:
            u = stack.pop()
            total += rewards[u]
            for v in reverse[u]:
                if component[v] == -1:
                    component[v] = cid
                    stack.append(v)
        component_value.append(total)

    count = len(component_value)
    dag = [[] for _ in range(count)]
    indegree = [0] * count
    for u, v in edges:
        cu, cv = component[u], component[v]
        if cu != cv:
            dag[cu].append(cv)  # Parallel edges are harmless.
            indegree[cv] += 1

    # Each SCC can be fully collected before leaving it; DAG has no cycles.
    dp = [-1] * count  # -1 means not reachable from start.
    source = component[start]
    destination = component[target]
    dp[source] = component_value[source]
    queue = deque(i for i, d in enumerate(indegree) if d == 0)
    while queue:
        u = queue.popleft()
        for v in dag[u]:
            if dp[u] != -1:
                dp[v] = max(dp[v], dp[u] + component_value[v])
            indegree[v] -= 1
            if indegree[v] == 0:
                queue.append(v)

    return dp[destination]
