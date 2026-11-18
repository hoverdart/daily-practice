# Optimal explanation — Package Prefix Inventory

## Recognition signals

Many string **prefix** queries over a fixed catalog, with repeated names, strongly suggest a trie. The alphabet is small and fixed: 26 lowercase letters. Each node represents a prefix, not necessarily a complete word. The query asks for the **number** of matching words, so store a multiplicity counter at every reached node.

## Brute force versus optimal

**Naive:** for every prefix, scan all n words and compare the beginning of each string. In the worst case O(sum over queries of n × query length), or O(n q L) if L is the maximum query length. Extra space O(1) beyond output.

**Optimal:** insert each word into a trie. Increment the root count, then the count at each visited character node. For a query, follow characters until a missing transition (answer zero) or the prefix ends (answer that node's count). The empty prefix ends at the root, yielding n.

Let W be total catalog characters, P be total prefix-query characters, q be number of queries. Building and querying takes **O(W + P + q)** time. At most W+1 trie nodes exist; each has 26 integer edges and a count, so **O(W)** additional space (for a fixed alphabet), plus O(q) output. This has an up-front build cost but removes the n factor from every query.

### Copyable C++17 syntax

~~~cpp
struct Node {
    std::array<int, 26> next;
    int pass = 0;
    Node() { next.fill(-1); }
};
std::vector<Node> nodes(1);
int child = nodes[u].next[c - 'a'];
if (child == -1) {
    child = (int)nodes.size();
    nodes[u].next[c - 'a'] = child;
    nodes.emplace_back();
}
u = child;
~~~

## Invariant and correctness

After inserting any number of words, count at each node equals the number of inserted **occurrences** whose spelling contains that node's prefix. Initially all counts are zero. Every insertion visits exactly the prefixes of its word, incrementing each exactly once and no others. Therefore the invariant is maintained by induction. A query follows precisely the desired prefix; an absent transition means no inserted word has that prefix.

## Mistakes and edge cases

1. Count only terminal words; this loses longer words beginning with the prefix.
2. Deduplicate identical names; multiplicity is intentional.
3. Forget the empty prefix: its answer is the number of catalog occurrences.
4. Forget to initialize child indexes to -1; index 0 is already occupied by the root.
5. Keep an int& into nodes[u] and then call nodes.emplace_back(): reallocation may invalidate it. Assign child index **before** growing the vector, or re-index afterward.
6. Assume every prefix is a valid package name; intermediate nodes matter too.

## CS61B transfer

Tries provide path-based string indexing, analogous to recursive tree structures but branching on symbols. Contrast with HashMap exact-word lookups (excellent for equality, not automatically prefix counting), and with sorting + binary-searching both prefix boundaries. The trie also exercises amortized vector capacity growth and safe handling of indices versus references in C++. Review using a tiny hand-drawn trie for "a", "an", "ant", "an" and verify node counts.
