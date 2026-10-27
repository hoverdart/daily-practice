# Medium — Budgeted Distinct Signal Windows

A telemetry stream has n events. Event i has an integer **code** and a nonnegative integer **inspection cost**. A window is a nonempty contiguous subarray.

Count windows satisfying **both**:
1. Exactly k distinct codes occur in the window.
2. Total inspection cost is at most budget.

Return the count as a long.

Implement:

~~~java
public static long countWindows(int[] codes, int[] costs, int k, long budget)
~~~

## Examples

- codes=[1,2,1], costs=[1,2,1], k=2, budget=3 → **2** ([1,2] and [2,1]).
- codes=[7,7,7], costs=[0,0,0], k=1, budget=0 → **6** (every nonempty window).
- codes=[1,2], costs=[0,0], k=0, budget=0 → **0**.
- codes=[1,2,3], costs=[1,1,1], k=2, budget=1 → **0**.

## Constraints

0 ≤ n ≤ 100,000; codes.length == costs.length. Codes are signed integers in [-10^9,10^9]. 0 ≤ costs[i] ≤ 10^6. 0 ≤ k ≤ n; 0 ≤ budget ≤ 10^12. Do not modify the inputs.

Aim for **O(n) expected time and O(n) auxiliary space** using Java HashMap. Explain why subtracting two at-most counts yields exactly k, and why nonnegative costs are necessary for the sliding-window invariant.
