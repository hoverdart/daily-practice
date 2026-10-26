def longest_affordable_window(
    channels: list[int], costs: list[int], max_types: int, budget: int
) -> tuple[int, int]:
    left = 0
    total = 0
    freq: dict[int, int] = {}
    best_left, best_right = 0, 0

    for right, (channel, cost) in enumerate(zip(channels, costs)):
        total += cost
        freq[channel] = freq.get(channel, 0) + 1

        while total > budget or len(freq) > max_types:
            outgoing = channels[left]
            total -= costs[left]
            freq[outgoing] -= 1
            if freq[outgoing] == 0:
                del freq[outgoing]
            left += 1

        if right + 1 - left > best_right - best_left:
            best_left, best_right = left, right + 1

    return best_left, best_right
