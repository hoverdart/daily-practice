# Hard / Stretch — Half-Price Transit

A directed network has n stations 0..n-1 and edges [u,v,cost] with nonnegative cost. Travel 0 to n-1. Once or not at all, apply a coupon to one edge and pay floor(cost/2). Return minimum total cost, or -1 if unreachable.

Signature: `static long cheapestTrip(int n, int[][] edges)`

Examples: n=3, [[0,1,10],[1,2,10],[0,2,25]] -> 12; n=4, [[0,1,8],[1,3,8],[0,2,3],[2,3,20]] -> 12.
