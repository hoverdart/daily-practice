# Attempt — Package Prefix Inventory

Complete before opening reference/.

- Started / finished / minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force time / extra space:
- Optimal time / extra space:
- First failing test or C++ syntax issue:
- One invariant or mistake to revisit:

## Recognition and implementation checks

- What words in the prompt make a trie attractive versus checking every word for every prefix?
- What does count at the root represent? Why does it handle the empty prefix?
- How and where do duplicate names increase counts?
- Does a missing character transition mean zero matches?
- Why can a reference to trie[node].next[letter] become dangling after emplace_back()?
- What is the bound on the number of nodes? Is the 26-child representation a worthwhile tradeoff?
- What changes if names can contain arbitrary Unicode or if deletions are required?

## CS61B connections

- Compare trie shared-prefix structure to a search tree and a HashMap keyed by whole words.
- Distinguish trie traversal cost O(prefix length) from O(log number of words).
- Explain the vector growth and indexing choices in C++17.
