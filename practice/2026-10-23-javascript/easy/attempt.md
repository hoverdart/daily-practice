# Attempt — Insert a Maintenance Window

Complete this **before** opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and brute force
- What does "sorted, disjoint intervals" allow you to skip?
- What would sorting all n+1 intervals and merging cost?
- Why do [2,5] and [5,8] overlap under **closed** intervals?

## One-pass invariant
- Which intervals have already been copied into the answer?
- What do the current merged start and end represent?
- Why can an interval that initially lies after added later overlap the **expanded** merged interval?
- What is the earliest moment it is safe to append the merged interval?

## Complexity and JavaScript
- Time / output space / auxiliary space:
- Did I avoid mutating input inner arrays?
- Any bugs with negatives, empty input, or single-point intervals?

## Failed tests / hints / API friction

## After reference: one CS61B merge-sort/two-pointer connection

