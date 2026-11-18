#include <string>
#include <vector>

std::vector<int> countPackagePrefixes(
    const std::vector<std::string>& packages,
    const std::vector<std::string>& prefixes) {

    // TODO: Build a character-indexed trie with a count at each prefix node.
    // Count duplicate catalog entries, and handle the empty prefix.
    // Avoid keeping references to vector elements across emplace_back().
    (void)packages;
    (void)prefixes;
    return {};
}
