#include <stddef.h>

size_t count_capped_matches(const int *a, size_t na,
                            const int *b, size_t nb,
                            size_t quota) {
    if (quota == 0) return 0;

    size_t i = 0, j = 0, total = 0;
    while (i < na && j < nb) {
        if (a[i] < b[j]) {
            ++i;
        } else if (a[i] > b[j]) {
            ++j;
        } else {
            int id = a[i];
            size_t start_a = i, start_b = j;
            while (i < na && a[i] == id) ++i;
            while (j < nb && b[j] == id) ++j;

            size_t pairs = i - start_a;
            if (j - start_b < pairs) pairs = j - start_b;
            if (quota < pairs) pairs = quota;
            total += pairs;
        }
    }
    return total;
}

