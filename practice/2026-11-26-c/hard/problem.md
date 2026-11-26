# Cheapest Dispatch, Fewest Hops (Hard/stretch)

A directed network has n stations and m links, each with a nonnegative integer cost. From start to target, first minimize total cost; among routes of that cost, minimize the number of links. Return that cost, hop count, and the number of routes attaining **both** minima modulo 1,000,000,007. A route is a walk (revisits allowed); parallel links are distinct choices, even with identical endpoints and cost. The empty route is allowed when start=target. If unreachable return {-1,-1,0}.

Implement `Route best_dispatch(int n, const Edge *edges, int m, int start, int target)`, using `typedef struct { int from,to,weight; } Edge;` and `typedef struct { long long cost; int hops,ways; } Route;`. `1<=n<=200000`, `0<=m<=400000`, valid endpoints `[0,n)`, `0<=weight<=1000000000`. NULL edges is allowed for m=0. Inputs read-only. Free scratch allocations; allocation failure may abort. Aim for O(n+m log(m+1)) time and O(n+m) space (or indexed-heap equivalent).

Example: links `(0,1,0),(0,1,0),(1,3,5),(0,2,2),(2,3,3),(0,3,5)` yield `{5,1,1}` from 0 to 3; without the direct link, `{5,2,3}`. Zero-cost cycles do not create infinitely many optimal routes because every edge adds a hop.
