# Easy — Nearest Blocking Beacon

A one-way line of beacons transmits from left to right. Beacon i has an integer signal strength strengths[i]. For each beacon i, identify the **closest beacon strictly to its left** whose strength is **greater than or equal to** strengths[i]. A weaker beacon cannot block it.

Implement:

~~~js
function closestBlockingBeacon(strengths) { /* return indices */ }
~~~

Return an array of length n. Answer[i] is the index of the nearest qualifying earlier beacon, or -1 if none exists. Do not modify the input.

### Example

Input: [6, 2, 2, 7, 3, 8]

Output: [-1, 0, 1, -1, 3, -1]

At index 2, the immediately previous beacon has equal strength (2), so the answer is 1, not 0. At index 3, all earlier strengths are smaller than 7.

### Constraints

- 0 <= n <= 150,000.
- Each strength is an integer between -1,000,000,000 and 1,000,000,000.
- Desired: O(n) time and O(n) auxiliary space including the stack and output.

### Think first

You could scan left separately for every index. Which earlier indices can you permanently discard once a larger reading appears? What should remain on your stack?
