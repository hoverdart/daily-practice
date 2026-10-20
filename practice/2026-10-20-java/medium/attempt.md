# Attempt — Longest Stream with Limited Repeated Types

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What tells me the property is monotonic as the window shrinks?
- What would enumerating all windows cost?

## Frequency-map invariant
- `count[id]` represents:
- `repeatedTypes` represents:
- What happens at frequency 1→2 on insertion?
- What happens at frequency 2→1 on removal?
- Does 2→3 or 3→2 change the counter?
- When must I remove a zero-frequency map entry?

## Window reasoning
- Why does shrinking until `repeatedTypes <= k` leave a valid candidate?
- Why can `left` only move forward?
- How do I handle equal-length tie-breaking?

## Claimed complexity (time / space)

## Failed tests, hints, Java API friction
- `HashMap.getOrDefault`, `put`, `remove`:

## After reference
- What was the central invariant?
- One new surface story where this pattern applies:
