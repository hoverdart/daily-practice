def first_sufficient_slots(capacities: list[int], requests: list[int]) -> list[int]:
    result: list[int] = []
    for required in requests:
        lo, hi = 0, len(capacities)
        while lo < hi:
            mid = lo + (hi - lo) // 2
            if capacities[mid] < required:
                lo = mid + 1
            else:
                hi = mid
        result.append(lo if lo < len(capacities) else -1)
    return result
