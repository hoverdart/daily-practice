# Longest Window With Limited Handoff Types (Medium)

A production line records the device type processing each item, `types[i]`. When two **adjacent** items have different types, the directed change `(types[i-1], types[i])` is a **handoff type**. Repeated occurrences of the same ordered handoff count as **one distinct handoff type**; an unchanged type contributes no handoff. For example, `2→3` and `3→2` are different handoffs.

Find the **longest contiguous window of items** containing at most `k` distinct handoff types. Return its half-open bounds `[left, right)`. Break ties by smallest `left`. For an empty input, return `[0,0)`.

~~~java
public static int[] longestHandoffWindow(int[] types, int k)
~~~

**Example**

~~~text
types = [1, 2, 2, 3, 2, 2], k = 2
answer = [1, 6]
window = [2, 2, 3, 2, 2]     // only (2,3) and (3,2)
~~~

**Constraints:** `0 <= types.length <= 200_000`; type IDs are arbitrary signed 32-bit integers; `0 <= k <= types.length`. Do not mutate `types`. Target expected **O(n) time** and **O(n) worst-case extra space**.

**Interview checkpoints:** What does a frequency map count here—items or handoffs? Which single edge enters the window when `right` grows? Which edge leaves when `left` grows? How can two signed int IDs be encoded without collisions in a `long` key?