#include <array>
#include <string>
#include <vector>

std::vector<int> countPackagePrefixes(
    const std::vector<std::string>& packages,
    const std::vector<std::string>& prefixes) {

    struct Node {
        std::array<int, 26> next;
        int count = 0;
        Node() { next.fill(-1); }
    };
    std::vector<Node> trie(1); // index 0 is the empty prefix

    for (const std::string& word : packages) {
        int current = 0;
        ++trie[current].count;
        for (char ch : word) {
            const int letter = ch - 'a';
            int child = trie[current].next[letter];
            if (child == -1) {
                child = static_cast<int>(trie.size());
                trie[current].next[letter] = child;
                trie.emplace_back();
            }
            current = child;
            ++trie[current].count;
        }
    }

    std::vector<int> answers;
    answers.reserve(prefixes.size());
    for (const std::string& prefix : prefixes) {
        int current = 0;
        for (char ch : prefix) {
            current = trie[current].next[ch - 'a'];
            if (current == -1) break;
        }
        answers.push_back(current == -1 ? 0 : trie[current].count);
    }
    return answers;
}
