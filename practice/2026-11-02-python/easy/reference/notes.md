# Explanation — Prefix Counts in a Routing Directory

## Recognition signals
Many queries ask about **shared prefixes** of many strings, and repeated strings count independently. A trie stores the common prefixes once; a terminal boolean alone cannot answer multiplicity queries.

## Brute force versus optimal
A direct solution scans every route for each query and calls `startswith`: up to O(number of routes × number of queries × maximum prefix length). Sorting once and using two binary searches per prefix is another valid approach, but the trie offers a direct O(S + Q) expected traversal bound for total input characters S and query characters Q.

## Optimal invariant
Every trie node corresponds to one prefix p. Its `count` is **exactly the number of inserted route occurrences starting with p**. Before descending along a character, create the child if needed; increment its count for each inserted route, including duplicates. Increment the root once per route: its empty prefix matches all labels. A query walks its prefix edges; if an edge is absent, the answer is zero. Otherwise return the terminal node's count.

## Complexity
Expected time O(S + Q), assuming expected O(1) dictionary edge access; worst-case adversarial hash behavior is not covered by this bound. Space O(S + number of queries in the returned list); the trie has at most S+1 nodes. A fixed 26-way child array is also possible, trading simpler O(1) indexing for larger per-node memory.

## Common mistakes
- Recording counts only at terminal nodes, which misses longer labels.
- Using a set and losing duplicate multiplicities.
- Forgetting the root count for an empty query.
- Treating a nonexistent child as the same as the root.
- Returning a count for only *distinct* routes instead of occurrences.

## CS61B connections
Tries/prefix queries, tree traversal, hash-table edge maps, representation invariants, and space/time tradeoffs. The count field is an augmented tree statistic, similar to cached subtree sizes in other search trees.