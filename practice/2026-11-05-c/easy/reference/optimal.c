#include <stddef.h>

typedef struct Node {
    int reading;
    struct Node *next;
} Node;

Node *stable_faults_last(Node *head) {
    Node healthy = {0, NULL};
    Node faulty = {0, NULL};
    Node *healthy_tail = &healthy;
    Node *faulty_tail = &faulty;

    for (Node *p = head; p != NULL; ) {
        Node *next = p->next;      /* Preserve access to the remainder. */
        p->next = NULL;            /* Old links must not leak into a new chain. */
        if (p->reading >= 0) {
            healthy_tail->next = p;
            healthy_tail = p;
        } else {
            faulty_tail->next = p;
            faulty_tail = p;
        }
        p = next;
    }

    healthy_tail->next = faulty.next;
    return healthy.next != NULL ? healthy.next : faulty.next;
}

