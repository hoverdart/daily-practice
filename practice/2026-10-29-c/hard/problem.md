# Hard / Stretch — Maximum Reward with Setup Cooldown

You can perform optional jobs. Job `i` occupies a half-open time interval `[start, end)` and earns `reward` points. After completing one job, your equipment needs `cooldown` additional time units before the next job may start.

Select a subset and order it chronologically to maximize total reward. Jobs may be skipped. Return the maximum as a 64-bit integer. Do **not** mutate the input.

```c
typedef struct { int start, end; long long reward; } Job;
long long max_reward_with_cooldown(const Job *jobs, int n, int cooldown);
```

Two selected jobs `a` then `b` are compatible exactly when
`(long long)a.end + cooldown <= b.start`.

## Example

Jobs `{[0,3):8, [3,5):10, [5,7):9}` with `cooldown=1`: choose the first and third, total **17**. The first and second are incompatible because setup would finish at time 4.

## Constraints

- `0 <= n <= 200000`; `0 <= start < end <= 2000000000`.
- `0 <= reward <= 1000000000`, `0 <= cooldown <= 1000000000`.
- For `n == 0`, return 0. Return -1 on allocation failure or invalid nonempty input pointer.
- Aim for `O(n log n)` time and `O(n)` extra space.

## Interview prompts

Why is taking the highest-paying job first not always optimal? How does sorting by **end** time make a one-dimensional DP possible? How do you binary-search the last compatible job? Why must reward sums and time comparisons use 64-bit arithmetic?
