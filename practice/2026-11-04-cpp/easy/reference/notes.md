# Easy — Reference reasoning

## Recognition signals

A sequence of **push / pop / ask for aggregate** operations suggests a stack with a cached aggregate per entry. This is related to CS61B's stack ADT and invariants for recursive/linked structures. The aggregate here is maximum; similar augmented stacks can track minimum, greatest common divisor, or other prefix-combinable summaries.

## Brute force vs optimal

**Brute force:** store raw values and scan the whole stack on each Q. A single Q costs O(s) for stack size s; a long series of pushes and queries can take O(n²) overall. Keeping just a single mutable maximum breaks when undo pops the maximum: its predecessor is no longer known.

**Optimal:** each entry stores (value, max_so_far). For a push x, max_so_far = max(x, previous max_so_far), or x on an empty stack. Popping an entry automatically exposes its predecessor's correct maximum.

## Invariant and proof

After each command, stack[i].second equals the maximum of values at positions 0..i.

- Base: first push stores its own value.
- Push: old prefix maximum and new x together cover exactly the new prefix.
- Pop: the remaining entries are unchanged, and their stored prefix aggregates remain correct.
- Query: the last entry summarizes the entire current stack.

## Complexity

For n commands and q queries: O(n) total time and O(n) total storage including returned answers; auxiliary stack uses O(maximum stack depth). Every P, U and Q performs O(1) amortized work with std::vector; a Q's lookup itself is O(1).

## C++ / CS61B notes

- Use std::vector<std::pair<long long,long long>> and back()/emplace_back()/pop_back().
- Negatives require no fake zero sentinel; initialize from the first pushed value.
- Duplicates are safe because each position captures its own prefix state.
- Never use back() or pop_back() on an empty vector; the prompt guarantees valid commands.
- Java analogy: a stack holding a (reading, maximum) object; the vector owns its storage (RAII).

## Follow-up

Can you support both min and max using only one extra pair of aggregates per stack entry? Yes—each entry can hold (value,min_so_far,max_so_far).
