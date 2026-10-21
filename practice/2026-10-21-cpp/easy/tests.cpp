#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <unordered_set>
#include <vector>
#include "solution.cpp"

struct Chain {
    std::vector<std::unique_ptr<Node>> owned;
    Node* head = nullptr;
    std::vector<Node*> order;
    explicit Chain(const std::vector<int>& values) {
        Node* tail = nullptr;
        for (int v : values) {
            owned.push_back(std::make_unique<Node>(v));
            Node* p = owned.back().get();
            order.push_back(p);
            if (!head) head = p;
            else tail->next = p;
            tail = p;
        }
    }
};

static void check(const std::vector<int>& a, const std::vector<int>& b) {
    Chain x(a), y(b);
    std::vector<Node*> expected;
    size_t i = 0, j = 0;
    while (i < x.order.size() || j < y.order.size()) {
        if (j == y.order.size() ||
            (i < x.order.size() && x.order[i]->value <= y.order[j]->value))
            expected.push_back(x.order[i++]);
        else expected.push_back(y.order[j++]);
    }
    Node* merged = mergeCalibratedChains(x.head, y.head);
    std::unordered_set<Node*> seen;
    size_t k = 0;
    for (Node* p = merged; p; p = p->next) {
        assert(k < expected.size()); // also catches cycles
        assert(seen.insert(p).second);
        assert(p == expected[k++]); // identity, order, and stability
    }
    assert(k == expected.size());
}
int main() {
    check({}, {});
    check({1,3,3,8}, {2,3,7});
    check({}, {-3,-3,0});
    check({0,1,2}, {});
    check({1,1,1}, {1,1});
    check({-10,-5,0}, {-11,-5,9});
    std::mt19937 rng(210026);
    for (int t = 0; t < 900; ++t) {
        std::vector<int> a(rng()%35), b(rng()%35);
        for (int& v : a) v = static_cast<int>(rng()%13)-6;
        for (int& v : b) v = static_cast<int>(rng()%13)-6;
        std::sort(a.begin(),a.end()); std::sort(b.begin(),b.end());
        check(a,b);
    }
    std::vector<int> a(100000,1), b(100000,1);
    check(a,b);
    std::cout << "easy: all tests passed\n";
}
