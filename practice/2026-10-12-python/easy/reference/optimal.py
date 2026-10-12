from collections import deque


def first_unique_after_each(events: list[int]) -> list[int | None]:
    counts: dict[int, int] = {}
    candidates: deque[int] = deque()
    answer: list[int | None] = []

    for event in events:
        counts[event] = counts.get(event, 0) + 1
        if counts[event] == 1:
            candidates.append(event)

        while candidates and counts[candidates[0]] != 1:
            candidates.popleft()

        answer.append(candidates[0] if candidates else None)

    return answer
