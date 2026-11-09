"""Reference solution — read only after attempting easy/solution.py."""


def merge_service_windows(windows: list[list[int]]) -> list[list[int]]:
    if not windows:
        return []
    ordered = sorted(windows, key=lambda p: (p[0], p[1]))
    merged = [[ordered[0][0], ordered[0][1]]]
    for start, end in ordered[1:]:
        if start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged
