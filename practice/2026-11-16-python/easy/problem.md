# Easy — K-th Highest Incident Priority

An incident-response console receives a batch of signed integer priorities in their original arrival order. The console has capacity to retain only the **k most urgent incidents**. Equal values represent separate incidents.

Return the priority of the **k-th highest incident**, counting duplicates separately. The input is not sorted and must not be modified. You may scan the input only once after allocating your working structure; avoid sorting the entire input.

## Signature

~~~python
def kth_highest_priority(priorities: list[int], k: int) -> int:
    ...
~~~

**Constraints:** 1 ≤ len(priorities) ≤ 200,000; 1 ≤ k ≤ len(priorities); priorities are integers between −10^9 and 10^9. For a call outside the k constraints, raise **ValueError**.

## Examples

~~~python
kth_highest_priority([4, 1, 9, 9, -2], 3)  # 4
kth_highest_priority([8, 8, 8], 2)          # 8
kth_highest_priority([-7, -1, -5], 1)       # -1
kth_highest_priority([10, 2, 4, 6], 4)      # 2
~~~

Explain a full-sort baseline, then design an algorithm that uses a **min-heap of at most k entries**. State why the heap root, not its largest element, gives the answer. What changes if k is near n? Do not delete duplicate priorities.
