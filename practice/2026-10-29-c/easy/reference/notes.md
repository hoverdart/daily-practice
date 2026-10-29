# Recognition, reasoning, and reference — Run compression

**Recognition signals:** "consecutive equal items", "in-place", and "write a shorter representation" indicate run-length encoding with a read cursor and a write cursor. This is a two-pointer array/string transformation, not a hashing problem.

**Baseline:** Read runs into a separate output buffer and append the letter plus `sprintf`-formatted count. That is `O(n)` time and `O(n)` additional storage. It is straightforward but violates the in-place constraint.

**Optimal invariant:** At the beginning of each iteration, `read` is the first unread input byte, `[0,write)` is the fully encoded prefix, and `write <= read`. Count the entire next run *before* writing its encoding. For a singleton, output one byte; for a run of length `r >= 2`, output one byte plus `digits(r)` bytes, which is never more than `r`. Therefore the write cursor cannot overtake unread input.

**Decimal counts without allocation:** Repeated `count % 10` and `count /= 10` produce digits least-significant first. Write them into the destination, then reverse only that digit segment. Example: run length 12 temporarily emits `"a21"`, then swaps to `"a12"`. Write the final null terminator once, after the scan.

**Complexity:** `O(n)` time; every input character is counted once, and total emitted digits/reversals are at most `O(n)`. `O(1)` auxiliary memory (a few counters and a temporary byte). The output occupies the original buffer.

**Common mistakes:** emitting `a1` for singleton `a`; failing to reverse multi-digit counts; using `strlen` after modifying the string; forgetting `'\0'`; incrementing `write` past unread input; using `int` where `size_t` is natural; forgetting that `NULL` is explicitly supported.

**CS61B connections:** This is the same invariant discipline used in array-backed lists and two-pointer compaction. Prove the relationship between the read frontier and write frontier before coding; then off-by-one mistakes become easier to catch.
