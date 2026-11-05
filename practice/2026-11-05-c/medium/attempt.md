# Attempt — Count Calm Signal Intervals

Complete before opening reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Naive complexity:
- Optimal complexity and auxiliary space:

## Recognition and algorithm

- Why is this variable-size sliding window rather than nested enumeration?
- What invariant does a decreasing max deque represent? An increasing min deque?
- Why may equal values be removed from a deque's tail without losing correctness?
- Why does each index enter and leave a deque at most once?
- What must happen to deque heads when I increment left?
- Why does the latest right index contribute right-left+1 valid intervals?
- Why is the count long long and why must max-min be widened before subtraction?
- How do all-equal, alternating extremes, n=0, and tolerance=0 behave?

## C and CS61B

- Draw the four head/tail indices of the two array-backed deques.
- One wrong assumption / failed test / hint:
- One concept to revisit in 2–4 days:

