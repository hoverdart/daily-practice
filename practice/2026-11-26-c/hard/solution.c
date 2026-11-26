typedef struct { int from,to,weight; } Edge;
typedef struct { long long cost; int hops,ways; } Route;
Route best_dispatch(int n, const Edge *edges, int m, int start, int target) {
    (void)n; (void)edges; (void)m; (void)start; (void)target;
    /* TODO: implement. */
    return (Route){-1,-1,0};
}
