# Graphs + C/C++ Review

This is a practical interview/CS61B refresher. Read the recognition signals first; then use the snippets as templates.

# Part I — Graphs

## 1. Vocabulary and graph types

A graph G=(V,E) has vertices/nodes and edges. Degree is incident-edge count; in directed graphs distinguish indegree and outdegree. A path is a sequence of adjacent vertices. A simple path repeats no vertex. A cycle returns to its start.

- **Undirected:** edges work both ways. Friendships, roads if travel is symmetric.
- **Directed:** u→v does not imply v→u. Dependencies, web links.
- **Weighted:** edges carry cost/distance/time. Unweighted can be treated as every edge having weight 1.
- **Cyclic / acyclic:** cycles exist or do not. A directed acyclic graph is a **DAG**.
- **Connected:** in an undirected graph every pair is mutually reachable. Otherwise it has connected components.
- **Tree:** connected undirected acyclic graph. With V vertices it has V-1 edges and exactly one simple path between every pair.
- **Rooted tree:** a tree with a designated root, giving parent/child/depth structure.
- **DAG:** directed, no directed cycles. Supports topological order.
- **Complete graph:** every pair has an edge; Θ(V²) edges.
- **Bipartite:** vertices split into two groups and every edge crosses groups. Equivalent: 2-colorable; an undirected graph is bipartite iff it has no odd cycle.
- **Sparse vs dense:** sparse E is near V; dense E approaches V². This heavily affects representation choice.

### Secret graph signals
If the prompt contains **states + allowed transitions**, you probably have a graph even if it never says "graph": word transformations, lock combinations, game boards, grids, routes, prerequisite chains, social connections, configurations.

## 2. Representations

### Adjacency list
For each vertex, store neighbors.
- Space O(V+E)
- Iterate neighbors of u in O(deg(u))
- Edge lookup can be O(deg(u))
- Default for most interview graphs and sparse graphs.

Java: `List<List<Integer>> g`.
C++: `vector<vector<int>> g(n);`

### Adjacency matrix
`matrix[u][v]` says whether/what edge exists.
- Space O(V²)
- Edge lookup O(1)
- Iterate all neighbors O(V)
- Useful for dense/small graphs or repeated edge-existence queries.

### Edge list
Store `(u,v,w)` records.
- Space O(E)
- Great when algorithm scans all edges: Bellman-Ford, Kruskal.
- Poor for "give me u's neighbors" unless indexed.

## 3. DFS

**Mental model:** go deep before backing up. Stack, explicit or recursion.

Recursive pseudocode:
```
dfs(u):
    seen[u] = true
    for v in adj[u]:
        if !seen[v]:
            parent[v] = u
            dfs(v)
```

Iterative:
```
push(start)
mark start
while stack not empty:
    u = pop()
    for v in adj[u]:
        if unseen:
            mark v
            parent[v] = u
            push(v)
```

Use DFS for reachability, connected components, cycle detection, topological DFS, tree recursion, exhaustive/backtracking search. O(V+E) time, O(V) traversal state plus graph.

**Invariant:** seen means discovered; never recursively explore it as new again.

**Mistake:** marking only when popped/called can create duplicates in iterative traversals. Usually mark when enqueuing/pushing.

## 4. BFS

**Mental model:** concentric layers. FIFO queue.

```
queue start
seen[start] = true
dist[start] = 0
while queue:
    u = dequeue
    for v in adj[u]:
        if unseen:
            seen[v] = true
            dist[v] = dist[u] + 1
            parent[v] = u
            enqueue v
```

Use BFS for shortest number of edges in an unweighted graph, level-order exploration, nearest target, grid minimum steps. O(V+E).

**Core invariant:** when first discovered, a vertex has the minimum number of edges from the source. This works because the queue processes distance d before d+1.

### DFS vs BFS
Need any reachability/component? Either. Need minimum unweighted steps? BFS. Need recursive structural exploration/backtracking? DFS. Memory can differ: BFS stores a frontier; DFS stores a path/stack.

## 5. parent / edgeTo and path reconstruction

When discovering v from u, set `parent[v]=u`. To reconstruct target→source, repeatedly follow parents, then reverse. Search answers "can I reach it?"; parent answers "how?".

## 6. Connected components

Loop over every vertex. Each unseen vertex starts a DFS/BFS and increments component count. O(V+E). Isolated vertices count as components.

For many online connectivity queries, consider **union-find** instead.

## 7. Cycle detection

### Undirected
DFS with parent. Encountering a seen neighbor that is not the parent implies a cycle.

### Directed
A plain seen set is insufficient. Track 3 states:
- 0 unvisited
- 1 visiting/on recursion stack
- 2 finished

An edge to a **visiting** vertex is a back edge → cycle.

Kahn alternative: if topological processing outputs fewer than V vertices, a directed cycle exists.

## 8. Topological sort

A topological order places u before v for every edge u→v. Exists iff graph is a DAG.

### Kahn's algorithm
Compute indegrees; queue all zero-indegree vertices. Pop u, append it, decrement each outgoing neighbor's indegree; enqueue neighbors reaching zero. If output size < V, cycle.

O(V+E) with ordinary queue. A min-heap adds log V if deterministic smallest-first order is required.

### DFS method
DFS; append vertex **after** all outgoing neighbors finish. Reverse postorder. Must also detect cycles with visiting state.

Recognition: prerequisites, build systems, course order, task dependencies.

## 9. Shortest paths decision table

- **Unweighted / every edge same cost:** BFS, O(V+E).
- **Nonnegative weights:** Dijkstra, typically O((V+E) log V) with binary heap.
- **Negative edges possible:** Bellman-Ford, O(VE); can detect reachable negative cycles.
- **All-pairs, especially small/dense graph:** Floyd-Warshall, O(V³) time/O(V²) space.
- **DAG weighted shortest path:** topological order + relax edges, O(V+E), even with negative weights because no cycles.

### Relaxation
For edge u→v weight w:
`if dist[u] + w < dist[v], update dist[v]`.
This is the central shortest-path operation.

### Dijkstra
Initialize source 0, others infinity. Min-PQ by tentative distance. Pop cheapest state; skip stale entries; relax outgoing edges.

**Invariant:** with nonnegative edges, the minimum non-stale popped distance cannot later be improved.

Do NOT use ordinary Dijkstra with negative edges.

## 10. Bellman-Ford

Relax **every edge** V-1 times. Any simple shortest path has at most V-1 edges. A further successful relaxation indicates a reachable negative cycle.

Useful recognition: negative costs/rewards and need to detect negative cycles.

## 11. Floyd-Warshall

Dynamic programming over allowed intermediate vertices:
`dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.

Great when V is modest and you need distances between many/all pairs. Initialize diagonal 0, direct edges to weights, rest infinity.

## 12. Minimum spanning trees

An MST connects all vertices of a connected undirected weighted graph with minimum total edge weight. It is **not** a shortest-path tree.

### Kruskal
Sort edges ascending. Add edge iff its endpoints are in different union-find components. Stop after V-1 edges. O(E log E).

### Prim
Grow one tree. Maintain cheapest crossing edge to an unvisited vertex using a PQ. Typical adjacency-list implementation O(E log V).

Recognition: "connect all sites with minimum total construction cost." If question is "cheapest route from A to B", that is shortest path, not MST.

## 13. Union-Find / DSU

Supports:
- `find(x)`: representative/root
- `union(a,b)`: merge sets
- connectivity: `find(a)==find(b)`

Weighted/rank union + path compression gives near-constant amortized operations, formally O(α(V)).

Use for dynamic connectivity, cycle detection while adding undirected edges, Kruskal, grouping equivalence classes.

## 14. Priority queues in graph algorithms

A heap efficiently returns current minimum/maximum. Dijkstra needs minimum tentative distance; Prim needs cheapest frontier edge. A PQ does **not** automatically remove old entries after a better distance is inserted, so common pattern is:
`if (poppedDistance != dist[node]) continue;`

## 15. High-value search patterns

### Multi-source BFS
Put **all** sources into queue at distance 0 initially. Then BFS computes distance to nearest source. Examples: nearest hospital, spread of fire/rot, distance to nearest zero.

### Grid as graph
Each cell is a vertex; legal moves are edges. Usually do not build adjacency lists explicitly; generate 4/8 neighbors on demand. State may include more than (r,c), such as keys or remaining wall breaks.

### State-space graph
Node = complete information needed to determine legal future moves. Example `(station,couponUsed)`, `(r,c,keysMask)`, `(word)`. If arriving at the same physical location with different resources changes the future, those are different graph states.

### Bidirectional search
When source and target are known and branching is huge, BFS from both ends can reduce explored depth from roughly d to d/2 on each side. Requires ability to generate reverse neighbors or symmetric transitions.

### Backtracking / DFS
For "enumerate all choices" problems, choose → recurse → undo. Prune impossible branches early. Unlike ordinary graph DFS, you may intentionally revisit a value in another branch after undoing state.

### Memoized state search
If recursive search repeatedly reaches the same state, cache the answer for that state. This turns an exponential recursion into DP when the number of distinct states is manageable.

## 16. Graph complexity checklist

With adjacency lists, traversal is usually O(V+E), **not O(V·E)**. Ask:
1. How many states/vertices exist?
2. How many transitions/edges can be processed?
3. Is each edge processed once, twice, or many times?
4. Is there a heap factor log V?
5. Did I expand the state, e.g. V becomes V·K?

---

# Part II — C refresher

## 17. Compilation model

C source is compiled to object code, then linked.

```bash
gcc -std=c17 -Wall -Wextra -O2 main.c -o main
./main
```

Headers declare interfaces: `stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`, `stdint.h`.

## 18. Core types and arrays

Common types: `char, short, int, long, long long, float, double`; unsigned variants; `size_t` for sizes.

```c
int a[4] = {1,2,3,4};
size_t n = sizeof(a) / sizeof(a[0]);
```

Arrays usually decay to pointers when passed to functions, so length is not carried automatically.

## 19. C strings

A C string is a `char` array terminated by `'\0'`.

```c
char s[] = "hello";
printf("%zu\n", strlen(s));
```

`strlen` excludes terminator. Buffer size must include it. Never write beyond allocated capacity.

## 20. Pointers

`&x` gets address; `*p` dereferences.

```c
int x=5;
int *p=&x;
*p=9; // x is now 9
```

Pointer arithmetic advances in units of pointed-to type: `p+1` points to next element, not next byte.

C is pass-by-value. Passing a pointer copies the address, letting the callee mutate pointed-to data.

## 21. Structs

```c
struct Point { int x, y; };
struct Point p = {2,3};
struct Point *q = &p;
q->x = 7; // same as (*q).x
```

## 22. Heap memory

```c
int *a = malloc(n * sizeof *a);
int *z = calloc(n, sizeof *z);
a = realloc(a, new_n * sizeof *a);
free(a);
a = NULL;
```

Check allocation failures in production code. Be careful assigning `realloc` directly: failure returns NULL while original allocation remains allocated; a temporary pointer is safer.

Stack locals die at scope/function return. Heap allocation lives until `free`.

Common bugs: leak, double free, use-after-free, dangling pointer, uninitialized pointer, out-of-bounds access, returning address of a local variable, forgetting string terminator.

Function pointer idea:
`int (*cmp)(const void*, const void*)`; useful for callbacks like `qsort`, but not usually central in interviews.

---

# Part III — Modern C++ refresher

## 23. Compile + basic program

```bash
g++ -std=c++20 -Wall -Wextra -O2 main.cpp -o main
./main
```

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std; // convenient in interview code
```

`cout << x << '\n';` and `cin >> x;`.

C++ gives value semantics plus RAII and a large standard library. Prefer standard containers and smart ownership over manual `new/delete`.

## 24. string

```cpp
string s = "hello";
s.size();
s.empty();
s.push_back('!');
s.pop_back();
s.substr(start, len);
s.find("ell");             // string::npos if absent
reverse(s.begin(), s.end());
sort(s.begin(), s.end());
```

Strings own their memory and are far safer than raw `char*` for interview code.

## 25. References vs pointers

```cpp
int x=5;
int& r=x;   // alias; normally cannot be null/reseated
int* p=&x;  // address; can be null/reseated
```

Use references for required aliases/parameters; pointers when nullability or pointer semantics matter.

Parameter patterns:
```cpp
void f(int x);                 // copy small value
void g(vector<int>& a);        // mutate caller
void h(const vector<int>& a);  // read without copying
```

For large read-only objects, `const T&` is the interview default.

## 26. const

`const int x` cannot be modified.
`const vector<int>& v` means function cannot mutate v through that reference.

Pointer forms:
- `const int* p`: pointer to const int
- `int* const p`: const pointer to mutable int

## 27. Stack, heap, RAII

```cpp
vector<int> v(100); // object manages its own dynamic storage
```

When `v` leaves scope, destructor frees owned memory. This is RAII: resource lifetime tied to object lifetime.

Prefer automatic objects/containers. If ownership must be dynamic, modern C++ uses `unique_ptr` or `shared_ptr` rather than raw owning pointers. For interview algorithms, you rarely need manual `new/delete`.

## 28. struct/class

```cpp
class Counter {
    int value;          // private by default in class
public:
    Counter(int v): value(v) {}
    void inc(){ ++value; }
    int get() const { return value; }
};
```

`struct` members are public by default; `class` members private by default. Constructors establish invariants; destructors release resources. Standard containers already handle their own resources.

## 29. Templates

Templates parameterize code by type:
```cpp
template <typename T>
T twice(T x){ return x+x; }
```
STL containers/algorithms are templates: `vector<int>`, `vector<string>`.

## 30. STL container cheat sheet

- `vector<T>`: dynamic array; O(1) indexing, amortized O(1) push_back. Default sequence choice.
- `array<T,N>`: fixed-size array with STL interface.
- `deque<T>`: efficient push/pop at both ends.
- `list<T>`: doubly linked list; O(1) erase with iterator, no random access. Rare interview default.
- `stack<T>`: LIFO adapter: push/top/pop.
- `queue<T>`: FIFO: push/front/pop.
- `priority_queue<T>`: max-heap by default.
- `set<T>`: ordered unique keys, O(log n).
- `unordered_set<T>`: hash set, average O(1).
- `map<K,V>`: ordered map, O(log n).
- `unordered_map<K,V>`: hash map, average O(1).

Choose ordered map/set when sorted iteration, predecessor/successor, or logarithmic worst-case tree operations matter. Otherwise hash containers are often simplest.

## 31. vector essentials

```cpp
vector<int> v;
v.push_back(3);
v.emplace_back(4);
v.size();
v.empty();
v.back();
v.pop_back();
v[0];       // unchecked
v.at(0);    // bounds checked
vector<int> a(n, 0);
```

Range loop:
```cpp
for (int x : v) { }        // copies each x
for (int& x : v) { }       // mutable reference
for (const int& x : v) { } // no copy, read-only
```

## 32. iterators + algorithms

Most algorithms use half-open ranges `[begin,end)`.

```cpp
sort(v.begin(), v.end());
reverse(v.begin(), v.end());
auto it = find(v.begin(), v.end(), target);
bool ok = binary_search(v.begin(), v.end(), target);
auto lo = lower_bound(v.begin(), v.end(), target); // first >= target
auto hi = upper_bound(v.begin(), v.end(), target); // first > target
int mn = *min_element(v.begin(), v.end());
```

For sorted vector, index = `lower_bound(...) - v.begin()`.

## 33. lambdas and comparators

```cpp
sort(items.begin(), items.end(),
     [](const auto& a, const auto& b) {
         return a.second < b.second;
     });
```

Comparator answers whether a should come **before** b. It must behave like a strict ordering; do not use `<=`.

## 34. pair, tuple, auto

```cpp
pair<int,string> p = {3,"hi"};
cout << p.first;
auto [id,name] = p;

tuple<int,int,string> t = {1,2,"x"};
auto [a,b,s] = t;
```

`auto` asks compiler to infer static type; it does not make C++ dynamically typed.

## 35. priority_queue

Max heap:
```cpp
priority_queue<int> pq;
```

Min heap:
```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

Pairs are lexicographically ordered, so Dijkstra often uses:
```cpp
using P = pair<long long,int>;
priority_queue<P, vector<P>, greater<P>> pq;
```

## 36. Graph adjacency list in C++

Unweighted:
```cpp
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u); // only if undirected
```

Weighted:
```cpp
vector<vector<pair<int,int>>> g(n); // {neighbor, weight}
g[u].push_back({v,w});
```

### BFS
```cpp
vector<int> dist(n,-1);
queue<int> q;
dist[s]=0; q.push(s);
while(!q.empty()){
    int u=q.front(); q.pop();
    for(int v:g[u]) if(dist[v]==-1){
        dist[v]=dist[u]+1;
        q.push(v);
    }
}
```

### DFS
```cpp
void dfs(int u, const vector<vector<int>>& g, vector<bool>& seen){
    seen[u]=true;
    for(int v:g[u]) if(!seen[v]) dfs(v,g,seen);
}
```

## 37. Frequency map

```cpp
unordered_map<int,int> freq;
for(int x: nums) ++freq[x];
if(--freq[x]==0) freq.erase(x);
```

Membership:
```cpp
if(freq.count(x)) { }
// C++20: if(freq.contains(x)) { }
```

Beware: `freq[x]` inserts x with default value 0 if absent.

## 38. Sliding window

Typical "longest subarray satisfying condition":
```cpp
int left=0, best=0;
unordered_map<int,int> freq;
for(int right=0; right<(int)a.size(); ++right){
    ++freq[a[right]];
    while(/* window invalid */){
        if(--freq[a[left]]==0) freq.erase(a[left]);
        ++left;
    }
    best=max(best, right-left+1);
}
```

Invariant: after the while loop, current window is valid. Each endpoint moves forward at most n times → often O(n).

## 39. Two pointers

Sorted pair sum:
```cpp
int l=0,r=(int)a.size()-1;
while(l<r){
    long long s=(long long)a[l]+a[r];
    if(s==target) break;
    if(s<target) ++l;
    else --r;
}
```

Recognition: sorted data, pair constraints, shrinking interval, deduping, partition-like scans.

## 40. Binary search

Exact:
```cpp
int l=0,r=(int)a.size()-1;
while(l<=r){
    int m=l+(r-l)/2;
    if(a[m]==x) return m;
    if(a[m]<x) l=m+1;
    else r=m-1;
}
```

For "first true" monotonic predicate, use a half-open invariant:
```cpp
int l=0,r=n;
while(l<r){
    int m=l+(r-l)/2;
    if(ok(m)) r=m;
    else l=m+1;
}
// l is first true, possibly n
```

## 41. Dijkstra snippet

```cpp
const long long INF = 4e18;
vector<long long> dist(n, INF);
using P=pair<long long,int>;
priority_queue<P,vector<P>,greater<P>> pq;
dist[s]=0; pq.push({0,s});
while(!pq.empty()){
    auto [d,u]=pq.top(); pq.pop();
    if(d!=dist[u]) continue;
    for(auto [v,w]:g[u]){
        if(d+w<dist[v]){
            dist[v]=d+w;
            pq.push({dist[v],v});
        }
    }
}
```

## 42. Common C++ traps

### size_t / unsigned
`v.size()` is unsigned. Expressions like `v.size()-1` underflow when empty. In interview loops, after checking size, casting to `int` is often simpler.

### Iterator/reference invalidation
`vector::push_back` may reallocate, invalidating pointers/references/iterators into the vector. Erase also invalidates affected iterators.

### Copies vs references
`for(auto x : bigObjects)` copies. Use `const auto& x` to read without copying; `auto&` to mutate.

### Dangling references/pointers
Never return a reference/pointer to a local stack variable. Do not use references into a container after operations that invalidate them.

### Ownership
A raw pointer does not tell you who frees memory. Prefer values/containers/RAII; use smart pointers when dynamic ownership is actually required.

### Bounds
`v[i]` does no checking. Off-by-one errors remain your responsibility. Standard ranges are usually [begin,end).

### Hash map side effects
`m[key]` inserts if missing. Use `find`/contains when lookup should not mutate.

### Comparator bugs
For sort/PQ custom ordering, comparator must be consistent and strict. Returning `a <= b` is wrong.

## 43. C++ coming from Python / Java

| Intent | Python | Java | C++ |
|---|---|---|---|
| dynamic array | list | ArrayList | vector |
| hash map | dict | HashMap | unordered_map |
| hash set | set | HashSet | unordered_set |
| ordered map | — | TreeMap | map |
| queue | deque | ArrayDeque | queue/deque |
| min heap | heapq | PriorityQueue | priority_queue<T,vector<T>,greater<T>> |
| string length | len(s) | s.length() | s.size() |
| array length | len(a) | a.length | v.size() |
| append | a.append(x) | a.add(x) | v.push_back(x) |
| sort | a.sort() | Arrays.sort | sort(v.begin(),v.end()) |
| membership map | x in m | m.containsKey(x) | m.contains(x) (C++20) |
| iterate values | for x in a | for (T x : a) | for (const auto& x : a) |
| tuple-ish | tuple | record/class | pair/tuple |
| null | None | null | nullptr |

### Interview defaults to memorize
- Sequence: `vector<int>`
- Frequency/counts: `unordered_map<int,int>`
- Membership: `unordered_set<int>`
- FIFO BFS: `queue<int>`
- DFS: recursion or `stack<int>`
- Min-heap: `priority_queue<T,vector<T>,greater<T>>`
- 64-bit integer: `long long`
- Read large object without copy: `const T&`

## 44. Final recognition checklist

Before coding, ask:
1. What is a **state**?
2. What are legal **transitions**?
3. Is this unweighted shortest path (BFS), weighted nonnegative (Dijkstra), dependency ordering (toposort), connectivity (DFS/BFS/DSU), or connect-all-min-cost (MST)?
4. Do I need history in the state?
5. What invariant makes my algorithm correct?
6. What are V and E after state expansion?
7. In C++, am I copying accidentally, invalidating iterators, mixing signed/unsigned values, or relying on a max-heap when I need a min-heap?
