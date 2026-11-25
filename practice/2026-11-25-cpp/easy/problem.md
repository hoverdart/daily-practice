# Stable Dispatch Manifest — Easy

A dispatch log contains jobs in arrival order. Each job has an integer priority from 0 (lowest) to 100 (highest). Return the **original zero-based indices** of all jobs, ordered by decreasing priority. Jobs with the same priority must remain in arrival order. Do not mutate the input.

Implement:

```cpp
std::vector<int> stableDispatch(const std::vector<int>& priorities);
```

Examples:
- [2, 5, 2, 100, 5] -> [3, 1, 4, 0, 2]
- [0, 0, 0] -> [0, 1, 2]
- [] -> []

Constraints: 0 <= n <= 200,000; 0 <= priorities[i] <= 100. Aim for O(n + 101) time and O(101) auxiliary space excluding the returned vector. A comparison sort is a useful baseline, not the target.
