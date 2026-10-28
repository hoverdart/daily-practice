# Attempt — Count Overloaded Signal Windows

Complete **before** opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What do "contiguous", "count all windows", and monotone pair counts suggest?
- What is the time complexity of enumerating windows and recounting their pairs?
- Why is `atLeast(k) = total - atMost(k-1)` easier than counting overloaded windows directly?

## Sliding-window invariants
- What does `freq[x]` count for the current interval?
- When inserting x with old frequency f, why add f collision pairs?
- When removing x with old frequency f, why subtract f-1?
- After shrinking, why are exactly `right-left+1` valid windows ending at right?
- Why does each pointer move at most n times?
- Why must k=0 be handled before subtracting 1?

## C++ and reflection
- Why are `long long` counters necessary at n=200000?
- When should a zero-frequency key be erased from `unordered_map`?
- Expected time / auxiliary space:
- Failed cases / hints / C++ syntax friction:
- One transferable frequency-map invariant:

