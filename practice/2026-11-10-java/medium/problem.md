# Count Affordable Mixed-Channel Bursts (Medium)

A telemetry stream gives two parallel arrays: channel[i] identifies the channel for event i (possibly negative), and cost[i] is the nonnegative resource cost of that event. A **burst** is a nonempty contiguous interval [l..r].

A burst is acceptable when **both** conditions hold:
1. It uses at most maxDistinct different channel IDs.
2. The sum of its event costs is at most budget.

Implement:

~~~java
public static long countAffordableBursts(int[] channel, int[] cost,
                                         int maxDistinct, long budget)
~~~

Return the total number of acceptable nonempty bursts. Do not change the input arrays.

Example:

~~~text
channel = [4,4,7,4], cost = [2,3,1,2]
maxDistinct = 2, budget = 5
answer = 7
// Four singletons and three adjacent pairs; both length-3 intervals cost 6.
~~~

Constraints: 0 <= n = channel.length = cost.length <= 200_000; channel[i] is any signed 32-bit integer; 0 <= cost[i] <= 1_000_000_000; 0 <= maxDistinct <= n; 0 <= budget <= 1_000_000_000_000_000 (10^15). Empty bursts are **not** counted. Return long: the result can exceed Integer.MAX_VALUE.

Target **expected O(n) time** using a hash map, O(d) auxiliary memory for at most d channel frequencies, where d <= n.

Interview checkpoints: What precisely is stored in the map? Why is the window's validity monotone under shrinking? For fixed right, how many valid choices of left are there? Why can't negative costs be allowed with this reasoning?
