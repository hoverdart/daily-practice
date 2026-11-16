"""Reference solution — heap of the top k encountered incidents."""
import heapq


def kth_highest_priority(priorities: list[int], k: int) -> int:
    if not 1 <= k <= len(priorities):
        raise ValueError("k must be between 1 and len(priorities)")

    # heap[0] is the smallest of the k largest priorities seen so far.
    heap = priorities[:k]
    heapq.heapify(heap)
    for priority in priorities[k:]:
        if priority > heap[0]:
            heapq.heapreplace(heap, priority)
    return heap[0]
