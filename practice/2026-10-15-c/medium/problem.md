# Medium — Longest Bounded Channel Window

A factory's event stream records channel codes from 0 through 255. Find the length of the **longest contiguous** segment containing **at most k distinct channel codes**.

Implement:

    int longest_channel_window(const int *events, int n, int k);

Example: events=[1,2,1,3,3,2,2], k=2 gives 4 from [3,3,2,2]. If k=0, the answer is 0 even when the stream is nonempty. If n=0, answer 0.

Constraints: 0 <= n <= 100000, 0 <= k <= 256, each events[i] is in [0,255]. Input is read-only. Aim for **O(n+256) time** and **O(256) extra space**. You may use a fixed-size C frequency array rather than a hash table.

Think about when a code becomes distinct, and when it stops being present after the left boundary moves. This revisits the sliding-window frequency invariant from earlier attempts.
