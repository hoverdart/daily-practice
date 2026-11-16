"""Reference: O(n) sliding window with a deliberately stale max count."""


def longest_consensus_segment(labels: list[int], k: int) -> int:
    counts: dict[int, int] = {}
    left = 0
    max_seen_frequency = 0
    best = 0

    for right, value in enumerate(labels):
        counts[value] = counts.get(value, 0) + 1
        max_seen_frequency = max(max_seen_frequency, counts[value])

        # A stale maximum may overestimate this window's true maximum.
        # That is safe when we only need the maximum attainable length.
        while right - left + 1 - max_seen_frequency > k:
            outgoing = labels[left]
            counts[outgoing] -= 1
            if counts[outgoing] == 0:
                del counts[outgoing]
            left += 1

        best = max(best, right - left + 1)

    return best
