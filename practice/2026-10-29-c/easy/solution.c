#include <stddef.h>

/* Rewrite commands in place. Return length excluding '\0'. */
size_t compress_command_runs(char *commands) {
    (void)commands;
    /* TODO: scan runs, write one letter, then decimal count if > 1. */
    return 0;
}
