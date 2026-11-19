#include <stdlib.h>

typedef struct AlertNode {
    int id;
    struct AlertNode *next;
} AlertNode;

AlertNode *keep_solo_alerts(AlertNode *head) {
    /* Stack-allocated sentinel is never returned: only its next pointer is. */
    AlertNode dummy = {0, head};
    AlertNode *tail = &dummy;
    AlertNode *cur = head;

    while (cur != NULL) {
        AlertNode *end = cur->next;
        while (end != NULL && end->id == cur->id) {
            end = end->next;
        }

        if (cur->next == end) {
            /* Exactly one node in this run: reuse it. */
            tail->next = cur;
            tail = cur;
        } else {
            /* Repeated run: free every node before end. */
            while (cur != end) {
                AlertNode *next = cur->next;
                free(cur);
                cur = next;
            }
        }
        cur = end;
    }

    /* Important when the list ends in a repeated run. */
    tail->next = NULL;
    return dummy.next;
}
