# Medium — Recognition and Explanation

**Recognition signals:** “longest contiguous segment,” “at most K distinct,” “extend right, repair by moving left,” and a requirement to count repeated elements. This is a **variable-size sliding window**.

**Brute force:** enumerate every `[l,r]` and count distinct labels with a set. Incrementally maintaining the set per left endpoint costs `O(n²)` time and `O(n)` space. Rebuilding a set for every window is even slower.

**Optimal approach:** keep `freq`, a `Map<label,count>` for exactly the active window `[left,right]`. Add the new right element, then **while** `freq.size > k`, remove the leftmost occurrence and advance `left`. Delete keys when their count reaches zero. After repair, the window is valid; update the best answer only when its length is **strictly greater** than the current best, preserving earliest-start ties.

**Invariant:** at the end of each outer iteration, `freq` exactly represents the current valid window and contains at most `k` keys. For each fixed right endpoint, this is the leftmost valid start and hence the longest valid window ending there.

**Why linear despite nested loops?** `right` moves forward `n` times; `left` also moves forward at most `n` times total. Each Map update is average-case `O(1)`. Overall `O(n)` expected time and `O(min(n,k+1))` auxiliary space.

**Pseudocode:**

    left=0; freq=empty; best=[0,0]
    for right in 0..n-1:
        increment freq[tags[right]]
        while number_of_keys(freq)>k:
            decrement freq[tags[left]]
            delete key if count becomes zero
            left++
        if right-left+1 > best.length:
            best=[left,right-left+1]

**Common mistakes:** using a Set instead of counts (fails on duplicates); forgetting `Map.delete` at zero; shrinking once instead of until valid; updating before shrinking; replacing earliest tie with later equal window; confusing `map.length` with `map.size`; using `map[key]` instead of `map.get(key)`.

**JavaScript API:** `freq.set(x,(freq.get(x) ?? 0)+1)`; `freq.size`; `freq.delete(x)`. `??` is useful because zero is a valid count.

**CS61B connection:** hash-table average-case lookup and amortized analysis. Compare the prior minimum-cover window: there you shrink while **valid** to minimize; here you shrink while **invalid** to maximize.