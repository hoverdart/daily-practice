# Prefix Counts in a Routing Directory (Easy)

A service keeps a multiset of lowercase routing labels. Duplicate labels represent distinct active endpoints. For each query prefix, report **how many labels begin with that prefix**.

Implement:

```python
def prefix_route_counts(routes: list[str], queries: list[str]) -> list[int]:
    ...
```

- Each route is a lowercase a–z string; routes may repeat. An empty route is allowed and matches only the empty prefix.
- Each query is a lowercase prefix, possibly empty. The empty prefix matches **every** route, including empty routes.
- Return one integer per query, in original query order.
- Do not mutate either input.

**Examples**

```python
routes = ["ab", "abc", "ab", "b", ""]
queries = ["", "a", "ab", "abc", "ac", "b"]
# answer: [5, 3, 3, 1, 0, 1]
```

**Constraints:** Up to 100,000 routes and 100,000 queries; combined length of all routes and queries up to 500,000 characters. Aim for **O(total characters)** expected time, not a full scan of all routes per query.

**Interview prompts:** Which data structure reuses shared prefixes? What should a node count mean? When do you increment counts for duplicate routes? What does the root count represent?