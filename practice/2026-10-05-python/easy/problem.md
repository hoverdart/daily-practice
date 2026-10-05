# First Revisited Station

A delivery robot records the station ID it reaches after each hop. Return the **first station whose arrival is a revisit**, meaning the first value encountered while scanning left-to-right that has appeared earlier.

If every arrival is unique, return `None`.

## Signature

```python
def first_revisited(stations: list[int]) -> int | None:
```

## Examples

- `[4, 7, 2, 7, 4]` → `7`
- `[5, 5, 5]` → `5`
- `[1, 2, 3]` → `None`
- `[]` → `None`

## Constraints

- `0 <= len(stations) <= 200_000`
- Station IDs may be negative.
- Do not modify the input.

## Complexity goal

Aim for expected **O(n)** time and **O(n)** auxiliary space.
