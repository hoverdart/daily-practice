#include <stdlib.h>

typedef struct AlertNode {
    int id;
    struct AlertNode *next;
} AlertNode;

AlertNode *keep_solo_alerts(AlertNode *head) {
    /* TODO: scan equal-ID runs, free entire repeated runs, preserve unique nodes.
       Do not allocate replacement nodes. Return the new head. */
    return head;
}
