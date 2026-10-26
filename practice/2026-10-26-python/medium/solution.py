def longest_affordable_window(
    channels: list[int], costs: list[int], max_types: int, budget: int
) -> tuple[int, int]:
    """Return the earliest longest half-open window satisfying both limits."""
    # TODO: Sliding window with a channel frequency map and running cost.
    # Shrink while EITHER limit is violated; update best only after repair.
    raise NotImplementedError("Implement longest_affordable_window")
