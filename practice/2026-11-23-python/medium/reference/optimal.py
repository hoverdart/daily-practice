"""Reference: subtract counts of two bounded at-most-distinct windows."""


def count_signature_windows(signatures: list[int], k: int, max_length: int) -> int:
    if k <= 0 or max_length <= 0 or not signatures:
        return 0

    def count_at_most(limit: int) -> int:
        if limit <= 0:
            return 0
        counts: dict[int, int] = {}
        left = 0
        distinct = 0
        total = 0
        for right, value in enumerate(signatures):
            if counts.get(value, 0) == 0:
                distinct += 1
            counts[value] = counts.get(value, 0) + 1

            while distinct > limit or right - left + 1 > max_length:
                removed = signatures[left]
                counts[removed] -= 1
                if counts[removed] == 0:
                    del counts[removed]
                    distinct -= 1
                left += 1

            # Every suffix ending at 'right' and starting in [left, right] works.
            total += right - left + 1
        return total

    return count_at_most(k) - count_at_most(k - 1)
