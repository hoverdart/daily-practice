# Easy — Next Higher Voltage Reading

A sensor records one integer voltage per second. For every index `i`, report how many seconds until the **first strictly higher** reading to its right. If no such reading exists, report `0`.

Implement:

```java
public static int[] secondsUntilHigher(int[] readings)
```

Example: `[3, 1, 4, 4, 5]` → `[2, 1, 2, 1, 0]`. The reading `4` at index 2 must wait until index 4 because an **equal** reading at index 3 does not qualify.

Constraints: `0 <= readings.length <= 100_000`; values are signed 32-bit integers. Do not modify the input. Return a new array of the same length.

**Target:** O(n) time and O(n) auxiliary space. Explain why each index enters and leaves the stack at most once.

Recognition question: what does a question about the *next strictly greater element to the right* suggest?