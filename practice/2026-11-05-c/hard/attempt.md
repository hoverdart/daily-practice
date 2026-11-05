# Attempt — Mandatory Edges on Every Fastest Route

Complete before opening reference/.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Repeated-BFS brute-force runtime:
- Optimal time and space:

## Graph recognition and proof

- What do vertices/edges represent? Why is this unweighted shortest path?
- Why do I need forward BFS from s and reverse-graph BFS from t?
- What equality characterizes an edge that belongs to **at least one** shortest s-to-t route?
- Why does a shortest route cross exactly one directed edge from layer k to k+1 for every k from 0 to D-1?
- Why does a layer with exactly one *eligible edge* make that edge mandatory?
- Why does a layer with two eligible edges guarantee neither is mandatory?
- Why are parallel edges separate identities even when endpoints match?
- How do I avoid counting paths (which may be astronomically many)?
- What happens when source == target, t is unreachable, and the input has self-loops?

## C / CS61B review

- How do adjacency heads and next arrays represent a graph without C++ vectors?
- Why does marking vertices at enqueue time bound BFS to O(n+m)?
- Why must I allocate output indices and free all temporary arrays?
- One invariant/bug to revisit in 2–4 days:

