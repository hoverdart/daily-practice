# Prefix Router Ledger — reasoning and CS61B connection

## Recognition signals
Many dynamic insert/delete operations and **prefix-count** queries suggest a trie (prefix tree). A HashMap of complete words supports exact lookup, but a query like "how many labels start with ca?" still scans keys. Sorting the active words can help static prefix searches, but dynamic multiplicity and deletion complicate updates.

## Brute force → optimal
Brute force uses a Map from word to multiplicity and loops over all distinct words for every count: O(number of distinct words × prefix length) per query in the worst case. A trie shares prefixes. Each node has `children: Map<char,node>`, `pass` (number of active word copies whose path reaches this node), and `end` (number of copies ending here). The root's `pass` counts all active labels.

**Add invariant:** increment root.pass and each traversed node.pass; increment terminal.end. Duplicate inserts increase counts rather than create a second path.

**Remove invariant:** first walk the entire word without modifying counts. Only if the terminal.end > 0, decrement terminal.end and pass along the saved path. Optional pruning removes a child subtree only when its pass becomes zero; it cannot affect another active word. Never decrement on an absent word or on a prefix that was never a complete word.

**Count:** traverse the prefix and return terminal pass, or 0 if missing. Empty prefix returns root.pass.

## Complexity
For a command whose argument length is L, expected O(L+1) time with Map children; total O(sum of argument lengths + number of commands). Space is O(number of distinct trie nodes), bounded by the total length of distinct inserted labels (plus query output). Character-by-character lookup avoids repeatedly comparing full strings.

## Common mistakes
- Counting distinct labels instead of **copies**.
- Decrementing counts when a removal fails, producing negative pass.
- Checking pass>0 instead of end>0 for exact-word existence.
- Forgetting the empty-prefix query.
- Deleting a shared prefix branch that other words still need.
- Using `map[key]` rather than `Map.get` / `Map.set` in JavaScript.
- Assuming the trie automatically sorts query results; this task returns **counts**, not lexicographic suggestions.

## CS61B connections
Tries for string prefixes; recursive/tree node invariants; Map-based children vs 26-element arrays; hash table average-case lookup; amortized node creation/deletion. Interview extension: return top-k suggestions by augmenting nodes with metadata, then discuss update costs.
