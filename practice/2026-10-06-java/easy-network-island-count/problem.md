# Easy — Network Island Count

A lab has `n` computers numbered `0..n-1`. An undirected cable `[u,v]` means direct communication; reachability is transitive. Return the number of disconnected communication networks.

Signature: `static int countNetworks(int n, int[][] cables)`

Examples: `n=5, [[0,1],[1,2],[3,4]] -> 2`; `n=4, [] -> 4`; `n=1, [] -> 1`.