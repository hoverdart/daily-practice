# Attempt — Archive Range Count Queries

Complete **before** reading reference/.

- Start / finish / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- First failing test or syntax hesitation:
- Brute-force runtime / auxiliary space:
- Optimal runtime / auxiliary space:

## Recognition and proof

- Which detail allows binary search rather than hashing or a linear scan?
- What are the *two* insertion boundaries for inclusive [low, high]?
- Why is the second boundary the first element **strictly greater** than high?
- What happens when an endpoint is absent? What if it is INT_MIN or INT_MAX?
- What happens when low > high, the archive is empty, or every ID is duplicated?
- Why is taking the difference between two sorted-array iterators valid?
- Does converting that distance to int fit the given constraints?

## C++ and CS61B reflection

- Write std::lower_bound and std::upper_bound signatures from memory.
- Why are random-access vector iterators useful for binary search?
- One off-by-one error, complexity misconception, or follow-up to revisit:
