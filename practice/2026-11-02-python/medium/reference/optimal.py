def longest_policy_compliant_window(
    events: list[int], caps: dict[int, int]
) -> tuple[int, int]:
    freq: dict[int, int] = {}
    left = 0
    best = (0, 0)

    for right, x in enumerate(events):
        freq[x] = freq.get(x, 0) + 1

        # Before inserting x, all caps held. Only x can now be over limit.
        while freq.get(x, 0) > caps.get(x, 1):
            y = events[left]
            freq[y] -= 1
            if freq[y] == 0:
                del freq[y]
            left += 1

        if right + 1 - left > best[1] - best[0]:
            best = (left, right + 1)

    return best
