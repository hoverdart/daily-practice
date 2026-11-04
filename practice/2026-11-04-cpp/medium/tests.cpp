#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "solution.cpp"

static std::vector<int> brute(const std::string& s, const std::string& p) {
    std::vector<int> result;
    if (p.size() > s.size()) return result;
    std::array<int,26> need{};
    for (char c:p) if (c!='?') ++need[c-'A'];
    for (int left=0; left+static_cast<int>(p.size()) <= static_cast<int>(s.size()); ++left) {
        std::array<int,26> have{};
        for (int j=0; j<static_cast<int>(p.size()); ++j) ++have[s[left+j]-'A'];
        bool good=true;
        for (int c=0;c<26;++c) if (have[c] < need[c]) good=false;
        if (good) result.push_back(left);
    }
    return result;
}

int main() {
    assert((wildcardSignatureMatches("BACAB","A?B")==std::vector<int>{0,2}));
    assert((wildcardSignatureMatches("AACBA","AA?")==std::vector<int>{0}));
    assert((wildcardSignatureMatches("ABC","??")==std::vector<int>{0,1}));
    assert((wildcardSignatureMatches("ABAB","AA")==std::vector<int>{}));
    assert((wildcardSignatureMatches("AB","A??")==std::vector<int>{}));
    assert((wildcardSignatureMatches("","?")==std::vector<int>{}));
    assert((wildcardSignatureMatches("AAAA","AA")==std::vector<int>{0,1,2}));
    assert((wildcardSignatureMatches("ABCBAC","ABC")==std::vector<int>{0,2,3}));

    std::mt19937 rng(1130426);
    for (int t=0;t<2600;++t) {
        int n=static_cast<int>(rng()%24);
        int m=1+static_cast<int>(rng()%13);
        std::string s(n,'A'),p(m,'A');
        for (char& c:s) c=static_cast<char>('A'+rng()%5);
        for (char& c:p) c=(rng()%5==0)?'?':static_cast<char>('A'+rng()%5);
        assert(wildcardSignatureMatches(s,p)==brute(s,p));
    }
    std::string big(250000,'A');
    std::string pattern=std::string(80000,'A')+std::string(20000,'?');
    auto result=wildcardSignatureMatches(big,pattern);
    assert(result.size()==150001);
    assert(result.front()==0 && result.back()==150000);
    std::cout << "medium: all tests passed\n";
}
