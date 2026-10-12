def count_exactly_k(events: list[int], k: int) -> int:
    if k <= 0:
        return 0

    def at_most(limit: int) -> int:
        if limit < 0:
            return 0

        counts: dict[int, int] = {}
        left = 0
        total = 0

        for right, event in enumerate(events):
            counts[event] = counts.get(event, 0) + 1

            while len(counts) > limit:
                outgoing = events[left]
                counts[outgoing] -= 1
                if counts[outgoing] == 0:
                    del counts[outgoing]
                left += 1

            total += right - left + 1

        return total

    return at_most(k) - at_most(k - 1)
