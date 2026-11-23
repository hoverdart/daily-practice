"""Easy starter: implement multi-source unweighted shortest paths."""

def nearest_repair_hops(n: int, links: list[tuple[int, int]], hubs: list[int]) -> list[int]:
    """Minimum number of undirected links from each vertex to any hub; -1 if none."""
    # TODO: Build an adjacency list and a distance array initialized to -1.
    # TODO: Seed one deque with every distinct hub at distance zero.
    # TODO: BFS; mark distances when enqueuing, not when dequeuing.
    raise NotImplementedError("implement nearest_repair_hops")
