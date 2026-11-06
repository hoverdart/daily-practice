"use strict";

function minimumCompliantSwitchCost(switchCost, prerequisites) {
  const n = switchCost.length;
  if (n === 0) return 0;
  const needed = new Int32Array(n);
  for (const [before, after] of prerequisites) needed[after] |= 1 << before;
  const states = 1 << n;
  const dp = new Float64Array(states * n);
  dp.fill(Infinity);
  for (let first = 0; first < n; first++) {
    if (needed[first] === 0) dp[(1 << first) * n + first] = 0;
  }
  for (let mask = 1; mask < states; mask++) {
    const offset = mask * n;
    for (let last = 0; last < n; last++) {
      const cost = dp[offset + last];
      if (!Number.isFinite(cost)) continue;
      for (let next = 0; next < n; next++) {
        const bit = 1 << next;
        if ((mask & bit) !== 0 || (needed[next] & mask) !== needed[next]) continue;
        const index = (mask | bit) * n + next;
        const candidate = cost + switchCost[last][next];
        if (candidate < dp[index]) dp[index] = candidate;
      }
    }
  }
  let best = Infinity;
  for (let last = 0; last < n; last++) best = Math.min(best, dp[(states - 1) * n + last]);
  return Number.isFinite(best) ? best : -1;
}

module.exports = { minimumCompliantSwitchCost };
