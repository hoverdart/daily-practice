# Medium — Shortest Incident Evidence Segment

## Story

An event pipeline emits diagnostic event codes, represented by lowercase strings. A forensic query asks for the shortest **contiguous** segment containing a required *multiset* of events. Required codes may repeat: `["auth","auth","db"]` demands **two** auth events and **one** db event. Other codes are harmless.

The event `"#"` is a hard **reset barrier**: no valid segment may contain it. Thus evidence cannot be collected across resets.

Implement:

```js
function shortestEvidenceWindow(codes, required) // returns [start, end)
```

Return the zero-based half-open indices of the shortest valid segment. Break equal-length ties by **smaller start index**. Return `[-1,-1]` if no segment exists. If `required` is empty, return `[0,0]`.

## Examples

```text
codes    = ["auth","misc","auth","db","reset","auth","db"]
required = ["auth","auth","db"]
answer   = [0,4]  // "reset" above is a normal code, not "#"

codes    = ["a","a","#","b","a","b","a"]
required = ["a","b","a"]
answer   = [4,7]

codes    = ["a","#","b"]
required = ["a","b"]
answer   = [-1,-1]
```

## Constraints

- `0 <= codes.length <= 200_000`, `0 <= required.length <= 200_000`.
- All codes are nonempty strings. The barrier `"#"` is reserved and never appears in `required`.
- Case-sensitive equality.
- The input arrays must not be modified.

## Interview prompts

- What does `missing` count when a required code has multiplicity three?
- How do you shrink a *valid* window instead of expanding it?
- What exact state must be reset at `"#"`?
- Why does the algorithm stay linear even with a nested `while`?

