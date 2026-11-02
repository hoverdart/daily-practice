def longest_policy_compliant_window(
    events: list[int], caps: dict[int, int]
) -> tuple[int, int]:
    """Return earliest longest half-open interval respecting per-ID caps."""
    # TODO: Maintain exact window-local counts in a dict.
    # Expand right; while the *new* ID violates its cap, shrink left.
    # Careful: cap=0 can remove the new ID entirely from the dict.
    raise NotImplementedError("Implement longest_policy_compliant_window")
