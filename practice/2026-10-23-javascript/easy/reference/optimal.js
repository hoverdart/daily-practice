"use strict";

function insertMaintenanceWindow(intervals, added) {
  const result = [];
  let [start, end] = added;
  let i = 0;

  // Entirely before the new interval (strict, because endpoints are closed).
  while (i < intervals.length && intervals[i][1] < start) {
    result.push([...intervals[i]]);
    i++;
  }

  // Overlap can grow as we absorb existing intervals.
  while (i < intervals.length && intervals[i][0] <= end) {
    start = Math.min(start, intervals[i][0]);
    end = Math.max(end, intervals[i][1]);
    i++;
  }
  result.push([start, end]);

  while (i < intervals.length) {
    result.push([...intervals[i]]);
    i++;
  }
  return result;
}

module.exports = { insertMaintenanceWindow };

