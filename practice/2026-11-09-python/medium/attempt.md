# Attempt — Smallest Complete Sensor Snapshot

Complete this before looking at reference/.

- Start / finish / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal expected time and auxiliary space:
- First failed test, hint, or missing Python API:

## Recognition and invariant

- Which words identify a variable-size sliding window with *multiplicities*?
- What does need[id] = 2, 0, or -2 mean?
- What does the global number missing count? Why does it count **occurrences**, not just distinct IDs?
- When an incoming id is not requested, must it enter the dictionary?
- When an incoming requested ID has already been over-supplied, why is missing unchanged?
- When removing an ID, exactly when does missing increase?
- Why is it safe to shrink every time missing == 0?
- Where should I update my best answer? How do I break ties by earliest start?
- Why do the outer and inner loops together move pointers only O(n) times?

## Edge cases and CS61B

- What does empty required mean? What if a request cannot be satisfied?
- Did I preserve the half-open end index?
- Which CS61B hash-table properties make average dictionary operations O(1)?
- Explain Python dict membership, get, and integer-frequency update syntax from memory.
- One precise invariant or mistake to rehearse in 2–4 days:
