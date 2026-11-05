# Stable Linked-List Triage — Recognition and Explanation

## Recognition signals

The list must be **stable**; nodes must be **reused**; only next pointers may change; extra space must be constant. Think linked-list partition and two output chains with dummy/sentinel nodes. Sorting by reading value would violate stability and do unnecessary work.

## Brute force versus optimal

**Baseline:** Walk input nodes and copy values into two arrays (healthy/faulty), then rewrite node readings in the desired order. This could be O(n) time and O(n) space, but explicitly violates the no-copy/no-change-readings contract. A legal but slow alternative repeatedly finds an out-of-place node and splices it; a naive rescan can take O(n^2) time.

**Optimal:** Maintain two lists, each with a dummy head and tail pointer. Detach each input node by preserving its old next pointer and then clearing next. Append the node to its matching list. Concatenate healthy to faulty, and choose the first nonempty list as the answer. Every node is visited once and each append is O(1).

## Invariant and proof

After processing k original nodes, the healthy chain consists of exactly the nonnegative nodes among those k, in their original order. The faulty chain consists of exactly the negative nodes among those k, also in their original order. Both chains terminate at NULL and no node is included twice. Appending the next node at the correct tail maintains the invariant. At the end, concatenation gives the required stable order.

The dummy nodes are temporary stack objects whose **next** pointers point to real list nodes. We never return a pointer to the dummy itself.

## Complexity

O(n) time, O(1) auxiliary space. No heap allocations; nodes themselves are pre-existing input. This is valid even for n=200,000 (no recursion).

## Common mistakes

- Overwriting p->next before saving where to continue loses the remaining input.
- Appending without detaching leaves stale links, possibly creating cycles after concatenation.
- Treating zero as faulty; stable means preserve order among equal readings too.
- Returning the address of a stack-allocated dummy (dangling pointer).
- Forgetting empty partitions or NULL input.
- Accidentally freeing nodes the caller still owns.

## CS61B connection

This is the sentinel-node principle from singly/doubly linked lists: a dummy head removes special-case first-insertion logic. Explicit head/tail invariants mirror those needed for LinkedList, SLList, and deque implementations. In C, the ownership contract and exact order of pointer assignments are particularly important.

