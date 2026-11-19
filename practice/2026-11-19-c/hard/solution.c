#include <stddef.h>

int min_relay_turns(const char *const *grid, int rows, int cols) {
    /* TODO: 0-1 BFS over (row,col,previous_direction).
       Use a dynamically growing deque; push-front for 0-cost continuation
       and push-back for 1-cost turns. Mark distances, not just visited cells.
       Free every heap allocation before returning. */
    (void)grid;
    (void)rows;
    (void)cols;
    return -1;
}
