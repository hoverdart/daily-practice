# Easy — Calibration Undo Stack

An instrument receives a sequence of commands. A **P** command pushes a signed calibration reading onto a stack. A **U** command undoes (pops) the most recent reading. A **Q** command asks for the **maximum reading currently on the stack**.

Implement:

~~~cpp
struct AuditCommand {
    char kind;       // 'P', 'U', or 'Q'
    long long value; // used only when kind == 'P'
};
std::vector<long long> runningPeaks(const std::vector<AuditCommand>& commands);
~~~

Return the answer to each Q, in order.

**Guarantees:** Every U and Q occurs when the stack is nonempty. At least one Q occurs. A P may push a negative reading, and duplicate readings are allowed.

### Example

Commands: P(-4), P(-9), Q, P(7), Q, U, Q, U, Q

Output: [-4, 7, -4, -4]

The second Q sees a maximum of 7; undoing that push restores the previous maximum.

### Constraints

- 1 ≤ number of commands ≤ 400,000
- -1,000,000,000 ≤ pushed reading ≤ 1,000,000,000
- O(1) worst-case work per Q is expected; amortized O(1) per push/pop is acceptable.
- Use a vector as a LIFO stack; do not sort the stack after every command.

### Think first

A scan from bottom to top answers Q correctly, but costs O(stack size) each time. Can each stack entry carry enough history to recover the maximum after a pop without rescanning?
