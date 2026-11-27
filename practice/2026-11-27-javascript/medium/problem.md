# Shortest Archive Cut (Medium)

A telemetry archive contains a chronological array of integer event IDs. A retention rule allows each distinct ID to occur at most `cap` times in the archive **after** a deletion. You may delete one contiguous block (possibly empty or the entire array). Return the minimum number of elements to delete so every ID remaining outside that block satisfies the cap.

Implement `shortestArchiveCut(ids, cap)` in solution.js. Return a nonnegative integer length, not the block itself. Do not mutate ids.

## Examples
- `ids=[1,2,1,3,2], cap=1` -> 2. Delete the first two entries; the remaining IDs are distinct.
- `ids=[7,7,7,7], cap=2` -> 2.
- `ids=[1,2,3], cap=1` -> 0; no deletion needed.
- `ids=[1,2,3], cap=0` -> 3; every event must be deleted.
- `ids=[-1,-1,0,0,-1], cap=1` -> 3; remove the first three entries, leaving [0,-1].

## Constraints
- 0 <= ids.length <= 200,000
- IDs are integers in [-10^9, 10^9].
- cap is an integer in [0, 200,000].
- The whole-array deletion is always allowed.
- Aim for expected O(n) time.

Run `node tests.js`. Suggested time: 25–40 minutes.
