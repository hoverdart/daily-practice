# Easy — Compress Repeated Command Runs

A device sends commands as a null-terminated C string of lowercase letters. Consecutive repetitions can be compacted **in place**: emit the letter, followed by its run length in decimal **only if the run has length at least 2**. A singleton stays as just its letter.

Implement:

```c
size_t compress_command_runs(char *commands);
```

Return the new string length **excluding** the terminating `'\0'`, and terminate the result. The input buffer has exactly enough capacity for its original contents plus the null terminator; you may not allocate another array or use a second string. `commands == NULL` should return 0.

## Examples

- `"aaabbc"` → `"a3b2c"`, return 5
- `"abccdddd"` → `"abc2d4"`, return 6
- `"zzzzzzzzzzzz"` → `"z12"`, return 3
- `""` → `""`, return 0

## Constraints

- Original length `0 <= n <= 200000`; characters are `a` through `z`.
- Runs of length 10 or more require multi-digit counts.
- Aim for `O(n)` time and `O(1)` auxiliary space.
- Never write past the original null terminator's allocated slot.

## Interview prompts

Why is the compressed output never longer than the original? How can you emit decimal digits without a temporary string? Explain the read/write pointer invariant, including the moment when a run is counted.
