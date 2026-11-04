# Medium — Wildcard Signature Matches

A telemetry stream is an uppercase string S. A signature P consists of uppercase letters and question marks. Each '?' represents **one arbitrary uppercase letter**.

Find every zero-based starting index where a **contiguous substring of S of length |P|** can be rearranged to match P after replacing each '?' with exactly one letter.

The remaining literal letters must match **with multiplicity**. Rearrangement is allowed, but changing or dropping non-wildcard letters is not.

Implement:

~~~cpp
std::vector<int> wildcardSignatureMatches(const std::string& stream,
                                          const std::string& signature);
~~~

Return the matching indices in increasing order.

### Example

S = "BACAB", P = "A?B"

Answer = [0, 2].
- "BAC" contains A and B; the remaining C fills '?'.
- "ACA" lacks B.
- "CAB" contains A and B; C fills '?'.

More examples:
- S="AACBA", P="AA?" → [0].
- S="ABC", P="??" → [0,1].
- S="ABAB", P="AA" → [].
- If |P| > |S|, return [].

### Constraints

- 0 ≤ |S| ≤ 250,000
- 1 ≤ |P| ≤ 250,000
- Only A–Z in S; only A–Z and '?' in P.
- Aim for O(|S| + |P|) time and O(1) auxiliary counting space (26 letters), beyond output.

### Hint-free design question

A brute-force solution recounts every substring. If the window has a fixed length, how can you update *only* the two characters entering/leaving? What can a **positive frequency deficit** represent?
