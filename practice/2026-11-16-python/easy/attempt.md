# Attempt — K-th Highest Incident Priority

Fill this out **before** opening reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time and space:
- Optimal time and space:
- First failed test / Python API I forgot:
- Mistake to revisit in 2–4 days:

## Reasoning prompts

- Why does a min-heap, rather than a max-heap, hold the best k candidates?
- What must be true of the heap after seeing the first i values?
- Why is it safe to discard an arriving value when it is no larger than heap[0]?
- Why should duplicate priorities be preserved?
- Compare building a size-k heap with pushing every value and popping.
- What are heapify, heappush, heapreplace, and heappushpop used for?
- Which bound is O(n log k), and what is the simpler bound for sorting?
- Why is heap access O(1) but replacement O(log k)?

## CS61B transfer

- Relate heapq's root to heap swim/sink and priority queues.
- When would a streaming top-k solution matter more than a sorted batch?
- What should tomorrow's selection system review?
