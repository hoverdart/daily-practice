# Notes — Longest Distinct Sensor Window

## Recognition signals
“Longest contiguous”, “at most k”, and a condition repairable by moving the left boundary are sliding-window signals.

## Brute force -> optimal
Checking every subarray is O(n^2) windows. The optimal window never moves `left` backward: add the right item, then shrink until valid.

## Core invariant
After the inner while loop, `freq` exactly represents `readings[left..right]` and has at most k keys.

## Complexity
Expected O(n) time because each endpoint only moves forward. O(n) worst-case auxiliary space.

## Common mistakes
A set is insufficient because when left moves you must know whether another copy remains. Erase a key only when its count reaches zero. Handle k=0. `unordered_map::operator[]` inserts missing keys.

## CS61B connection
Hash tables plus the sliding-window interview extension. This intentionally revisits the recent low-confidence sliding-window attempt, now in C++.
