def count_light_batches(loads: list[int], limit: int) -> int:
    if limit <= 1:
        return 0

    left = 0
    product = 1
    total = 0
    for right, value in enumerate(loads):
        product *= value
        while product >= limit:
            product //= loads[left]
            left += 1
        total += right - left + 1
    return total

