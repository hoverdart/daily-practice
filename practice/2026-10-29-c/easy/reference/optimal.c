#include <stddef.h>

size_t compress_command_runs(char *commands) {
    if (!commands) return 0;
    size_t read = 0, write = 0;
    while (commands[read] != '\0') {
        char ch = commands[read];
        size_t count = 0;
        do { ++read; ++count; } while (commands[read] == ch);
        commands[write++] = ch;
        if (count > 1) {
            size_t first_digit = write;
            do {
                commands[write++] = (char)('0' + count % 10);
                count /= 10;
            } while (count);
            for (size_t i = first_digit, j = write - 1; i < j; ++i, --j) {
                char tmp = commands[i]; commands[i] = commands[j]; commands[j] = tmp;
            }
        }
    }
    commands[write] = '\0';
    return write;
}
