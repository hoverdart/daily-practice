# Easy — Insert a Maintenance Window

A service schedules maintenance as sorted, **pairwise non-overlapping closed time intervals**. The existing intervals are already ordered by start time. A new maintenance request arrives, and touching endpoints count as overlap: [2,5] and [5,8] must merge.

Implement:

~~~javascript
function insertMaintenanceWindow(intervals, added) {
  // Return a fresh array of [start,end] intervals.
}
~~~

**Input:** intervals is an array of [start,end] pairs, sorted by start, with intervals[i][1] < intervals[i+1][0]. The new pair added has start <= end. Endpoints are safe integers between -1e9 and 1e9. There may be zero existing intervals.

**Output:** sorted, disjoint closed intervals after inserting and merging added. **Do not mutate** intervals, its inner arrays, or added. Return fresh inner arrays.

**Example 1**

- intervals = [[1,3],[7,9],[12,14]], added = [3,12]
- output = [[1,14]] (the new request bridges all three intervals)

**Example 2**

- intervals = [[-5,-3],[2,4]], added = [-1,0]
- output = [[-5,-3],[-1,0],[2,4]]

**Example 3**

- intervals = [], added = [8,8]
- output = [[8,8]]

**Constraints:** 0 <= intervals.length <= 200,000. Target **O(n) time** and **O(n) output space**, with O(1) auxiliary space beyond output. You must exploit sorted/disjoint input instead of re-sorting everything.

**Optional hint (only after attempting):** There are three consecutive regions: intervals strictly before the new request, intervals that overlap the *growing* merged request, and intervals strictly after it.

