#include <algorithm>
#include <utility>
#include <vector>

struct AuditCommand {
    char kind;
    long long value;
};

std::vector<long long> runningPeaks(const std::vector<AuditCommand>& commands) {
    // (actual reading, maximum of all readings up to this stack position)
    std::vector<std::pair<long long, long long>> stack;
    std::vector<long long> answers;
    stack.reserve(commands.size());

    for (const AuditCommand& command : commands) {
        if (command.kind == 'P') {
            const long long peak = stack.empty()
                ? command.value
                : std::max(command.value, stack.back().second);
            stack.emplace_back(command.value, peak);
        } else if (command.kind == 'U') {
            stack.pop_back();  // nonempty by contract
        } else {  // Q
            answers.push_back(stack.back().second);  // nonempty by contract
        }
    }
    return answers;
}
