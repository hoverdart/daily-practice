#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "solution.cpp"

static std::vector<long long> oracle(const std::vector<AuditCommand>& commands) {
    std::vector<long long> stack, answer;
    for (const auto& command : commands) {
        if (command.kind == 'P') stack.push_back(command.value);
        else if (command.kind == 'U') stack.pop_back();
        else answer.push_back(*std::max_element(stack.begin(), stack.end()));
    }
    return answer;
}

int main() {
    assert((runningPeaks({{'P',-4}, {'P',-9}, {'Q',0}, {'P',7},
                          {'Q',0}, {'U',0}, {'Q',0}, {'U',0}, {'Q',0}})
            == std::vector<long long>{-4,7,-4,-4}));
    assert((runningPeaks({{'P',-2}, {'P',-2}, {'Q',0},
                          {'U',0}, {'Q',0}}) == std::vector<long long>{-2,-2}));
    assert((runningPeaks({{'P',-1000000000}, {'Q',0}})
            == std::vector<long long>{-1000000000}));

    std::mt19937 rng(11042026);
    for (int trial = 0; trial < 1700; ++trial) {
        std::vector<AuditCommand> commands;
        int depth = 0;
        for (int i = 0; i < 80; ++i) {
            const int choice = static_cast<int>(rng() % 4);
            if (depth == 0 || choice <= 1) {
                commands.push_back({'P', static_cast<int>(rng() % 51) - 25});
                ++depth;
            } else if (choice == 2) {
                commands.push_back({'U', 0});
                --depth;
            } else commands.push_back({'Q', 0});
        }
        if (depth == 0) commands.push_back({'P',-7});
        commands.push_back({'Q',0});
        assert(runningPeaks(commands) == oracle(commands));
    }

    std::vector<AuditCommand> stress;
    constexpr int n = 120000;
    stress.reserve(2 * n);
    for (int i = 0; i < n; ++i) stress.push_back({'P', i-90000});
    for (int i = 0; i < n; ++i) stress.push_back({'Q',0});
    const auto result = runningPeaks(stress);
    assert(result.size() == static_cast<size_t>(n));
    assert(std::all_of(result.begin(), result.end(), [](long long x) { return x==29999; }));
    std::cout << "easy: all tests passed\n";
}
