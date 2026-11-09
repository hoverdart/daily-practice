"""Reference solution — read only after attempting medium/solution.py."""


def smallest_complete_snapshot(
    events: list[int], required: dict[int, int]
) -> tuple[int, int]:
    if not required:
        return (0, 0)

    # need[id] = requested occurrences minus occurrences currently in window.
    need = required.copy()
    missing = sum(required.values())
    left = 0
    answer = (-1, -1)
    best_length = len(events) + 1

    for right, value in enumerate(events):
        if value in need:
            if need[value] > 0:
                missing -= 1
            need[value] -= 1

        while missing == 0:
            length = right + 1 - left
            if length < best_length:
                best_length = length
                answer = (left, right + 1)

            outgoing = events[left]
            if outgoing in need:
                need[outgoing] += 1
                if need[outgoing] > 0:
                    missing += 1
            left += 1

    return answer
