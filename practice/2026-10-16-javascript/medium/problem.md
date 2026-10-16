# Medium — Prefix Router Ledger

An edge router maintains a **multiset** of active lowercase routing labels. Support a stream of commands:

- `["add", word]`: insert one copy of a nonempty label.
- `["remove", word]`: delete **one** copy if present; otherwise do nothing.
- `["count", prefix]`: report how many currently active labels (including duplicates) start with `prefix`. An empty prefix matches every active label.

Implement:

```js
function processPrefixOperations(operations) // array of counts, in query order
```

**Example**

```js
[
 ["add","cam"], ["add","camera"], ["add","cam"],
 ["count","cam"], ["remove","cam"], ["count","cam"],
 ["count","camera"], ["remove","missing"], ["count",""]
]
```

Output: `[3, 2, 1, 2]`.

**Constraints:** up to 100,000 commands; total length of all command words/prefixes <= 300,000; `word` contains only `a`–`z` and is nonempty for add/remove; `prefix` may be empty.

**Target:** O(total characters processed + number of commands) expected time. Do not scan all active words for each query. Avoid mutating the caller's operations.
