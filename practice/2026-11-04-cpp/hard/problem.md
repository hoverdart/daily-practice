# Hard / Stretch — Coordinated Relay Rendezvous

Two autonomous couriers start at distinct or identical vertices A and B in a **directed**, nonnegatively weighted road network. They depart at time 0 and travel independently until they meet at one of the listed synchronization hubs. Either courier may wait at the hub. Once both have arrived, they depart together from the hub and travel to the same destination T along the **same route**.

Find the **earliest possible arrival time at T**. If several synchronization hubs achieve that time, choose the hub with the **smallest numeric ID**. Return {-1,-1} if no hub is feasible.

Implement:

~~~cpp
struct Road {
    int from, to;
    long long travel;
};
std::pair<long long,int> earliestJointArrival(
    int n, const std::vector<Road>& roads,
    int sourceA, int sourceB, int destination,
    const std::vector<int>& hubs);
~~~

Roads are directed, so a road u→v does not imply v→u. Couriers can share vertices/edges on their independent legs; no edge capacities or collisions. Waiting is free. The destination need not itself be listed as a hub.

### Example

n=4; A=0; B=1; T=3; allowed hubs=[2,3]

Roads (from,to,time):
- (0,2,4), (1,2,7), (2,3,3)
- (0,3,50), (1,3,20)

At hub 2, they meet at time max(4,7)=7, then take 3 to T: arrival 10.
At hub 3, the independent fastest arrivals are 7 and 10, so the common arrival is also 10.
Answer: **{10,2}** because 2 is the smaller hub ID.

### Constraints

- 1 ≤ n ≤ 200,000; vertices are 0..n-1
- 0 ≤ number of roads ≤ 300,000
- 0 ≤ travel ≤ 1,000,000,000, including zero-time roads
- 0 ≤ number of listed hubs ≤ n (IDs valid; duplicates allowed)
- All valid arrival times fit in signed 64-bit integers.
- Aim for O((n+m) log n) time and O(n+m) space; avoid recursive DFS.

### Recognition questions

What must you know for each candidate hub v? Can you obtain all three needed distances in **three** shortest-path searches instead of one search per hub? How does reversing every directed road help you compute v→T distances?
