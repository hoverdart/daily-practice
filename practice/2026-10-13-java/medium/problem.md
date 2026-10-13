# Medium — Minimum Calibration Segment

An event stream must contain specified event IDs with specified minimum multiplicities. Find the shortest **contiguous inclusive** segment [left, right] meeting every quota. Break equal-length ties by the smallest left index; return [-1,-1] if impossible.

Implement `public static int[] shortestQuotaWindow(int[] events, int[] requiredIds, int[] minimumCounts)`. The two requirement arrays have equal length. For each i, the window must contain requiredIds[i] at least minimumCounts[i] times.

Example: events=[1,2,1,3,2,1], requiredIds=[1,2], minimumCounts=[2,1]. Return [0,2].

Constraints: events length 0..100000; requirement length 1..100000; requiredIds are distinct; quotas positive; IDs may be negative. Quota sums may exceed the event count. Do not mutate inputs.

Target: O(n+k) expected time and O(k) auxiliary space, assuming average O(1) map operations. Explain the meaning of need[id], have[id], and missing, and when adding/removing an event changes missing.
