#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned seed = 0x739af51du;
static unsigned rnd(void) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

static void check(const int *values, int n) {
    if (n == 0) {
        assert(stable_faults_last(NULL) == NULL);
        return;
    }
    Node *nodes = calloc((size_t)n, sizeof(*nodes));
    int *order = malloc((size_t)n * sizeof(*order));
    assert(nodes && order);
    for (int i = 0; i < n; ++i) {
        nodes[i].reading = values[i];
        nodes[i].next = i + 1 == n ? NULL : &nodes[i + 1];
    }
    int len = 0;
    for (int i = 0; i < n; ++i) {
        if (values[i] >= 0) order[len++] = i;
    }
    for (int i = 0; i < n; ++i) {
        if (values[i] < 0) order[len++] = i;
    }
    assert(len == n);
    Node *p = stable_faults_last(&nodes[0]);
    for (int i = 0; i < n; ++i) {
        assert(p == &nodes[order[i]]); /* identity and stable order */
        assert(p->reading == values[order[i]]);
        p = p->next;
    }
    assert(p == NULL); /* no extra nodes, no cycles, proper termination */
    free(order);
    free(nodes);
}

int main(void) {
    check(NULL, 0);
    int a[] = {5,-3,0,-1,8}, b[] = {-5,-4,-3}, c[] = {0,3,2};
    int d[] = {INT_MIN, INT_MAX, -1, 0, -1, INT_MIN, INT_MAX};
    check(a,5); check(b,3); check(c,3); check(d,7);
    int x = -1, y = 0;
    check(&x,1); check(&y,1);
    for (int t = 0; t < 9000; ++t) {
        int v[101];
        int n = (int)(rnd() % 101u);
        for (int i = 0; i < n; ++i) {
            v[i] = (int)(rnd() % 13u) - 6;
        }
        check(v,n);
    }
    const int n = 200000;
    int *big = malloc((size_t)n * sizeof(int));
    assert(big);
    for (int i = 0; i < n; ++i) big[i] = (i % 3 == 0 ? -i - 1 : i);
    check(big,n);
    free(big);
    puts("easy: stable linked-list triage passed");
    return 0;
}

