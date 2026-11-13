# Easy — First Full Network Merge

## Scenario

An operations center begins with `n` disconnected monitoring stations numbered `0..n-1`. A list of undirected links `links[i] = [u,v]` is installed in order. Return the **number of installation events** processed when all stations become mutually connected for the **first time**. Return `-1` if they never become connected. Self-links and duplicate links are allowed and still count as events. By convention, `n=0` and `n=1` are connected from the beginning, so return `0`.

## Signature

```js
function firstFullyConnected(n, links) { /* integer */ }
```

**Limits:** `0 <= n <= 100000`; `0 <= links.length <= 200000`; all endpoints valid when `n>0`. Do not mutate inputs.

## Examples

```js
firstFullyConnected(4, [[0,1],[2,3],[0,2]]) // 3
firstFullyConnected(3, [[0,1],[1,0],[1,2]]) // 3
firstFullyConnected(4, [[0,1],[2,3]])       // -1
firstFullyConnected(1, [])                  // 0
```

Explain a brute-force BFS-after-every-link approach, then implement a near-linear disjoint-set solution with a component count. Why do duplicate links not reduce that count? Why return `i+1`, not `i`?
