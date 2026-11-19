#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned rng = 0x419b21d7u;
static unsigned next_rand(void) {
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng;
}

static AlertNode *make_list(const int *a, int n) {
    AlertNode *head = NULL, **slot = &head;
    for (int i = 0; i < n; ++i) {
        AlertNode *node = malloc(sizeof *node);
        assert(node != NULL);
        node->id = a[i];
        node->next = NULL;
        *slot = node;
        slot = &node->next;
    }
    return head;
}

static void check(const int *a, int n) {
    int expected[128];
    assert(n <= 128);
    int m = 0;
    for (int i = 0; i < n;) {
        int j = i + 1;
        while (j < n && a[j] == a[i]) ++j;
        if (j == i + 1) expected[m++] = a[i];
        i = j;
    }
    AlertNode *out = keep_solo_alerts(make_list(a, n));
    AlertNode *p = out;
    for (int i = 0; i < m; ++i) {
        assert(p != NULL && p->id == expected[i]);
        AlertNode *next = p->next;
        free(p);
        p = next;
    }
    assert(p == NULL);
}

int main(void) {
    check(NULL, 0);
    int a[] = {-4,-4,1,3,3,6,8,8,10};
    check(a, (int)(sizeof a / sizeof a[0]));
    int b[] = {INT_MIN,INT_MIN,0,INT_MAX,INT_MAX};
    check(b, 5);
    int c[] = {1,1,1,1};
    check(c, 4);
    int d[] = {8};
    check(d, 1);
    int e[] = {1,1,2,3,3,4};
    check(e, 6);

    for (int t = 0; t < 5500; ++t) {
        int arr[128];
        int n = (int)(next_rand() % 121u);
        int value = -50;
        for (int i = 0; i < n; ++i) {
            value += (int)(next_rand() % 3u);
            arr[i] = value;
        }
        check(arr, n);
    }

    const int n = 200000;
    AlertNode *head = NULL, **slot = &head;
    for (int i = 0; i < n; ++i) {
        AlertNode *node = malloc(sizeof *node);
        assert(node);
        node->id = i / 2;
        node->next = NULL;
        *slot = node;
        slot = &node->next;
    }
    assert(keep_solo_alerts(head) == NULL);
    puts("easy: solo alerts passed");
    return 0;
}
