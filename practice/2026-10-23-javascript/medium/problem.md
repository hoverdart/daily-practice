# Medium — Shortest Required-Signal Window

A telemetry stream is an array of integer signal IDs. An auditor requires a **multiset** of IDs: for example, [7,7,3] means at least **two** occurrences of 7 and **one** occurrence of 3.

Find the **shortest contiguous subarray** of events containing every required ID with at least its required multiplicity. On ties, choose the **earliest starting index**.

Implement:

~~~javascript
function shortestRequiredSignalWindow(events, required) {
  // Return [start,end], both inclusive.
}
~~~

Return [-1,-1] if no such subarray exists. If required is empty, return [0,-1] (the empty window), regardless of events.

**Example 1**

- events = [4,7,2,7,3,7,2], required = [7,7,3]
- output = [3,5], because [7,3,7] is the shortest covering window.

**Example 2**

- events = [2,1,3,2,1,3], required = [1,2]
- output = [0,1], beating equally short later windows by earliest start.

**Example 3**

- events = [9,8,9], required = [9,9,9]
- output = [-1,-1].

**Constraints:** 0 <= events.length, required.length <= 200,000; IDs are signed 32-bit integers. Aim for **O(n+r)** expected time and **O(u)** extra space, where r = required.length and u is the number of distinct required IDs. Use JavaScript Map; do not sort the stream.

**Optional hint:** Track how many **individual required occurrences** are still missing, not just how many distinct types are missing. A frequency deficit can go negative if the current window has extras.

