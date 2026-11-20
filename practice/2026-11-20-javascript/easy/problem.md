# Easy — Filter Invalid Routing Markers

## Story

A routing log is a string of lowercase letters and structural markers `(` and `)`. Parentheses encode nested route groups. A corrupted event stream can contain unmatched markers. Remove the minimum number of parentheses so that the remaining parentheses are balanced; **never remove, reorder, or alter any other character**.

To make the expected output deterministic, use this tie policy: during a left-to-right scan, remove each closing parenthesis that has no matching earlier opening parenthesis. Afterward, remove **all opening parentheses that remain unmatched**. Preserve the relative order of all retained characters.

Implement:

```js
function sanitizeRoutingLog(text) // returns string
```

## Examples

```text
text = "a)b(c)d("      -> "ab(c)d"
text = "(a(b)"        -> "a(b)"
text = "x(y)z"        -> "x(y)z"
text = "))(("         -> ""
text = ""            -> ""
```

## Constraints

- `0 <= text.length <= 200_000`
- Characters are lowercase ASCII letters, `(`, or `)`.
- Return the complete sanitized string.

## Interview prompts

- Why can an unmatched closing bracket be discarded immediately?
- How do you remember positions of opening brackets while retaining letters?
- Compare repeated deletion on a string to building one output buffer.
- Give tight time and auxiliary-space bounds.

**Don't look at `reference/` until you've attempted the solution.**

