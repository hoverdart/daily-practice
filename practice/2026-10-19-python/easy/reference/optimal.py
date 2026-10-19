def count_zero_sum_spans(values: list[int]) -> int:
    seen: dict[int, int] = {0: 1}
    prefix = 0
    answer = 0
    for value in values:
        prefix += value
        answer += seen.get(prefix, 0)
        seen[prefix] = seen.get(prefix, 0) + 1
    return answer

