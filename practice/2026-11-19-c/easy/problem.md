# Easy — Solo Alerts in a Sorted Chain

A telemetry service stores alert IDs as a **nondecreasing** singly linked list. IDs that occur repeatedly in one batch are unreliable. Delete **every node** belonging to a run of length two or greater; only IDs that appeared **exactly once** survive.

For example, `-4 -> -4 -> 1 -> 3 -> 3 -> 6 -> 8 -> 8 -> 10` becomes `1 -> 6 -> 10`.

## Function

```c
typedef struct AlertNode {
    int id;
    struct AlertNode *next;
} AlertNode;

AlertNode *keep_solo_alerts(AlertNode *head);
```

Return the new head. **Reuse all surviving original nodes** without allocating replacement list nodes. Every removed node must be `free`d exactly once. The caller owns and frees the returned chain. The input nodes were individually allocated by the caller; do not return a pointer to a local variable.

## Constraints and behavior

- `0 <= n <= 200000`, IDs fit signed 32-bit `int`, input is nondecreasing.
- Input `NULL` means an empty list; return `NULL`.
- If every ID repeats, return `NULL`.
- A run with three or more copies is removed entirely, not truncated to one copy.
- O(n) time and O(1) additional space are expected (excluding the already-allocated input).

## Examples

- `[] -> []`
- `[2] -> [2]`
- `[1,1,2,3,3,4] -> [2,4]`
- `[-2,-2,-2,0,5,5] -> [0]`

Before writing C, sketch the head/tail pointers and decide how you reconnect the predecessor when a removed run starts at the head.
