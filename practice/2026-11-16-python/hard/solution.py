"""Hard starter: rerooted tree DP, with two iterative passes."""


def farthest_critical_distances(
    n: int, edges: list[tuple[int, int, int]], critical: list[int]
) -> list[int]:
    """Maximum weighted tree distance from each node to a marked node."""
    # TODO: Build the undirected adjacency list; make parent[] and traversal order.
    # TODO: Compute down[] in reversed order.
    # TODO: Compute up[] forward using the two best *distinct* child sources.
    raise NotImplementedError("implement farthest_critical_distances")
