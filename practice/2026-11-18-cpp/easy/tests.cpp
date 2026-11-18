#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "solution.cpp"

static std::vector<int> brute(
    const std::vector<std::string>& words,
    const std::vector<std::string>& queries) {
    std::vector<int> result;
    for (const auto& prefix : queries) {
        int count = 0;
        for (const auto& word : words) {
            if (word.size() >= prefix.size()
                && word.compare(0, prefix.size(), prefix) == 0) ++count;
        }
        result.push_back(count);
    }
    return result;
}

int main() {
    assert((countPackagePrefixes(
        {"core", "codec", "core", "config", "db"},
        {"co", "cor", "core", "db", "x", ""})
        == std::vector<int>{4, 2, 2, 1, 0, 5}));
    assert((countPackagePrefixes({}, {"", "a", "ab"})
        == std::vector<int>{0, 0, 0}));
    assert(countPackagePrefixes({"a", "aa"}, {}).empty());
    assert((countPackagePrefixes({"a", "a", "abc"}, {"a", "ab", "abc", "abcd", ""})
        == std::vector<int>{3, 1, 1, 0, 3}));

    std::mt19937 rng(18112026);
    for (int trial = 0; trial < 2800; ++trial) {
        int n = static_cast<int>(rng() % 43);
        int q = static_cast<int>(rng() % 31);
        std::vector<std::string> words(n), queries(q);
        for (auto& w : words) {
            int len = 1 + static_cast<int>(rng() % 7);
            for (int j = 0; j < len; ++j) w += char('a' + rng() % 4);
        }
        for (auto& p : queries) {
            int len = static_cast<int>(rng() % 7);
            for (int j = 0; j < len; ++j) p += char('a' + rng() % 4);
        }
        assert(countPackagePrefixes(words, queries) == brute(words, queries));
    }

    std::vector<std::string> huge(100000, std::string(50, 'a'));
    const auto result = countPackagePrefixes(
        huge, {"", "a", std::string(50, 'a'), std::string(51, 'a'), "b"});
    assert((result == std::vector<int>{100000, 100000, 100000, 0, 0}));

    std::cout << "easy: all tests passed\n";
}
