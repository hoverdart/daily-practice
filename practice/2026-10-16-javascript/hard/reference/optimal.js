"use strict";
function shortestKeycardEscape(grid) {
  const rows = grid.length;
  const cols = grid[0].length;
  let start = -1;
  for (let r = 0; r < rows; r++) {
    const c = grid[r].indexOf("S");
    if (c !== -1) start = r * cols + c;
  }
  const encode = (pos, mask) => pos * 16 + mask;
  const visited = new Uint8Array(rows * cols * 16);
  const queue = [[start, 0, 0]]; // [flattened position, collected-key mask, steps]
  visited[encode(start, 0)] = 1;
  const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
  for (let head = 0; head < queue.length; head++) {
    const [pos, mask, steps] = queue[head];
    const r = Math.floor(pos / cols);
    const c = pos % cols;
    if (grid[r][c] === "E") return steps;
    for (const [dr, dc] of directions) {
      const nr = r + dr, nc = c + dc;
      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
      const cell = grid[nr][nc];
      if (cell === "#") continue;
      if (cell >= "A" && cell <= "D" &&
          (mask & (1 << (cell.charCodeAt(0) - 65))) === 0) continue;
      let nextMask = mask;
      if (cell >= "a" && cell <= "d") nextMask |= 1 << (cell.charCodeAt(0) - 97);
      const nextPos = nr * cols + nc;
      const state = encode(nextPos, nextMask);
      if (visited[state]) continue;
      visited[state] = 1;
      queue.push([nextPos, nextMask, steps + 1]);
    }
  }
  return -1;
}
module.exports = { shortestKeycardEscape };
