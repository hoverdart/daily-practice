#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned rng = 0x734ac123u;
static unsigned rnd(void) {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return rng;
}
static int height(const Node *p) {
    if (!p) return 0;
    int a = height(p->left), b = height(p->right);
    return 1 + (a > b ? a : b);
}
static int slow_check(const Node *p) {
    if (!p) return 1;
    int a = height(p->left), b = height(p->right);
    return abs(a - b) <= 1 && slow_check(p->left) && slow_check(p->right);
}
int main(void) {
    assert(tree_is_balanced(NULL) == 1);
    Node leaves[] = {{1,NULL,NULL},{2,NULL,NULL},{3,NULL,NULL}};
    leaves[0].left = &leaves[1]; leaves[0].right = &leaves[2];
    assert(tree_is_balanced(&leaves[0]) == 1);
    leaves[2].left = NULL; leaves[0].right = NULL; leaves[1].left = &leaves[2];
    assert(tree_is_balanced(&leaves[0]) == 0);
    Node t[7] = {{0}};
    t[0].left=&t[1]; t[0].right=&t[2];
    t[1].left=&t[3]; t[2].left=&t[4];
    t[3].left=&t[5]; t[4].right=&t[6];
    assert(tree_is_balanced(&t[0]) == 0);
    for (int run = 0; run < 4000; ++run) {
        int n = (int)(rnd() % 90u);
        Node a[90] = {{0}};
        for (int i = 0; i < n; ++i) a[i].id = i;
        for (int i = 1; i < n; ++i) {
            for (;;) {
                int p = (int)(rnd() % (unsigned)i);
                Node **slot = (rnd() & 1u) ? &a[p].left : &a[p].right;
                if (!*slot) { *slot = &a[i]; break; }
            }
        }
        Node *root = n ? &a[0] : NULL;
        assert(tree_is_balanced(root) == slow_check(root));
    }
    Node chain[1500] = {{0}};
    for (int i = 0; i < 1499; ++i) chain[i].right = &chain[i+1];
    assert(tree_is_balanced(chain) == 0);
    puts("easy: balanced sensor hierarchy passed");
    return 0;
}
