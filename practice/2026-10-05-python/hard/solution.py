def min_battery_cost(n: int, edges: list[tuple[int, int, int]]) -> int:
    """Return minimum cost from 0 to n-1 with an optional one-use half-cost token."""

    # Here, we're using Dijkstra's algorithm to find the shortest path from node 0 to node n-1 in a graph represented by edges. The graph is undirected, and each edge has a cost. 
    # We can use a one-time token to halve the cost of one edge in our path, so we need to take into account the length of the path and whether we've used the token or not. We use a priority queue to explore the graph, keeping track of the current cost, node, and whether we've used the token. If we reach node n-1, we return the cost. If we exhaust all possibilities without reaching n-1, we return -1.
    from collections import defaultdict
    import heapq

    graph = defaultdict(list)
    for u, v, cost in edges:
        graph[u].append((v, cost))
        graph[v].append((u, cost))

    # (cost, node, token_used)
    pq = [(0, 0, False)] #This is our "starting" edge, with a cost of 0, starting at node 0, and not having used the token yet.
    visited = set()

    # HOW DIJKSTRA'S ALGORITHM WORKS:
    """
    Dijkstra's algorithm is a graph search algorithm that finds the shortest path from a starting node to all other nodes in a weighted graph. 
    It works by maintaining a priority queue of nodes to explore, where the priority is based on the current known shortest distance to that node. 
    The algorithm repeatedly extracts the node with the smallest distance from the queue, updates the distances to its neighbors, and adds them to
    the queue if they haven't been visited yet. This process continues until all nodes have been visited or the shortest path to the target node 
    has been found.

    Here, what we're doing is finding that shortest paths from node 0 to node n-1, but we also have the option to use a one-time token that 
    halves the cost of one edge in our path. To find that edge, we need to keep track of whether we've used the token or not as we explore the 
    graph. If we reach node n-1, we return the cost. If we exhaust all possibilities without reaching n-1, we return -1.

    """
    while pq: 
        cost, node, token_used = heapq.heappop(pq)

        if (node, token_used) in visited:
            continue
        visited.add((node, token_used))

        if node == n - 1: # when we reach the destination node, we return the cost of the path taken to get there.
            return cost

        for neighbor, edge_cost in graph[node]:
            # Normal cost
            heapq.heappush(pq, (cost + edge_cost, neighbor, token_used))
            # Half-cost if token not used
            if not token_used:
                heapq.heappush(pq, (cost + edge_cost // 2, neighbor, True))

    return -1  # If no path found

