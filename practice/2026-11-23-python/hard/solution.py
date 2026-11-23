"""Hard starter: iterative SCC decomposition followed by DAG dynamic programming."""

def max_collectible_value(
    rewards: list[int], edges: list[tuple[int, int]], start: int, target: int
) -> int:
    """Maximum one-time room rewards along a directed walk from start to target."""
    # TODO: Build forward and reverse graphs.
    # TODO: Compute finish order iteratively (no recursive DFS).
    # TODO: Run second DFS on the reverse graph to assign SCC IDs.
    # TODO: Sum rewards per SCC; build the condensation DAG.
    # TODO: Longest-path DP on the DAG from start component to target component.
    raise NotImplementedError("implement max_collectible_value")
