# Attempt — Closest Calibration Threshold

Complete **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What does the BST invariant let me discard after inspecting a node?
- What would visiting every node cost?
- How does this differ from binary search on an array?

## Invariant
- What does best represent after each visited node?
- Why can a subtree on the wrong side of target be skipped?
- How do I handle exact matches and smaller-value ties?

## Java, complexity, reflection
- Why can Math.abs(node.value - target) overflow?
- Why use iteration rather than recursion for a skewed tree?
- Time in terms of height h, balanced vs skewed:
- Auxiliary space:
- Failed tests / hints / syntax friction:
- One CS61B BST fact to remember:
