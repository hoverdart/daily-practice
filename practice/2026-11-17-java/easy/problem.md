# Oldest Unique Event in a Live Feed — Easy

A diagnostic feed delivers event IDs in arrival order. After each new event, report the **earliest-arriving event ID that has occurred exactly once in the entire feed so far**. An ID that appears two or more times is no longer unique, even if it appears again.

Implement:

~~~java
public static int[] earliestUniqueAfterEach(int[] eventIds)
~~~

Return an int array with exactly eventIds.length results, one after each arrival. Return -1 when no ID occurs exactly once. Input IDs are nonnegative, so -1 cannot be an actual ID. Do not modify the input.

Example:

~~~text
eventIds = [7, 9, 7, 3, 9, 3]
answers  = [7, 7, 9, 9, 3, -1]
~~~

Explanation: after the third arrival, ID 7 is duplicated, so 9 is the earliest unique ID. After the fifth arrival, 9 is duplicated too, so 3 takes its place.

**Constraints:** 0 <= n <= 200,000; 0 <= eventIds[i] <= 1,000,000,000.

Target **O(n) expected total time** and O(n) auxiliary space. Hash-based expected-time qualifications are acceptable.

Interview checkpoints: Why is repeatedly scanning the entire prefix too slow? How can a queue preserve arrival order even after the counts change? How often can an ID be enqueued, and how often can an old queue head be removed?

