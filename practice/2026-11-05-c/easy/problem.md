# Easy — Stable Triage of a Linked Queue

A sensor queue is represented by a **singly linked list** of nodes. A nonnegative reading means the sensor is healthy; a negative reading means it needs service. Reorder the list so that all healthy readings come first and all faulty readings come second, **preserving the original relative order within each group**.

Implement:

~~~c
typedef struct Node {
    int reading;
    struct Node *next;
} Node;

Node *stable_faults_last(Node *head);
~~~

**Important:** Reuse every original node exactly once. You may change next pointers but may not allocate, free, copy, or replace nodes. Do not modify readings. The list is initially acyclic. NULL is a valid input.

### Example

Input: 5 -> -3 -> 0 -> -1 -> 8 -> NULL

Output: 5 -> 0 -> 8 -> -3 -> -1 -> NULL

A zero reading is healthy. Duplicate values are distinct nodes whose relative order must be preserved.

### Constraints and expected performance

- 0 <= number of nodes <= 200,000
- readings are any signed 32-bit integers, including INT_MIN
- O(n) time; O(1) auxiliary space, not counting the existing nodes
- The returned tail must point to NULL, even if the original last node moved into the middle

### Think before coding

If you create one temporary head/tail pair for each category, how do you guarantee that appending a node does not also append the remainder of its old chain? What happens if one category is empty?

