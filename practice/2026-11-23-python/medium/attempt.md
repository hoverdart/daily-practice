# Attempt — K-Signature Window Budget

Complete before looking at `reference/`.

- Start / finish / time spent:
- Outcome (independent / hints / reference / unfinished):
- Confidence (1–5):
- Baseline complexity / optimal complexity:
- First failed test, hint, or Python dictionary syntax mistake:
- One pattern to revisit in 2–4 days:

## Window invariants

- Why can't one simple window directly count **exactly** k distinct windows as easily as **at most** k?
- Derive `exactly(k) = at_most(k) - at_most(k-1)`.
- What do `counts`, `distinct`, and `left` mean after shrinking?
- Why does `counts.pop(id)` or `del counts[id]` matter when a frequency reaches zero?
- Why does the **length cap** require shrinking even if the distinct cap is satisfied?
- For a fixed `right`, why are exactly `right-left+1` starting positions valid?
- What happens for `k=0`, `max_length=0`, duplicate values, and negatives?
- Why is the nested while still O(n) across all rights?
- How does this relate to CS61B hashing, amortized reasoning, and array indices?
