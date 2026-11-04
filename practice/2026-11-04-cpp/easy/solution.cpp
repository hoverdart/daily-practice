#include <vector>

struct AuditCommand {
    char kind;
    long long value;
};

std::vector<long long> runningPeaks(const std::vector<AuditCommand>& commands) {
    // TODO: maintain a stack of (pushed reading, maximum through this entry).
    // 'P' pushes; 'U' removes the top; 'Q' appends the current maximum.
    (void)commands;
    return {};
}
