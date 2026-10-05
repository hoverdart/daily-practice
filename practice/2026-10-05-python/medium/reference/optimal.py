def longest_stable_window(readings: list[int], k: int) -> int:
    if k <= 0:
        return 0
    counts = {}
    left = 0
    best = 0
    for right, code in enumerate(readings):
        counts[code] = counts.get(code, 0) + 1
        while len(counts) > k:
            outgoing = readings[left]
            counts[outgoing] -= 1
            if counts[outgoing] == 0:
                del counts[outgoing]
            left += 1
        best = max(best, right - left + 1)
    return best
