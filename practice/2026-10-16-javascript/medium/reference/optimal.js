"use strict";
function processPrefixOperations(operations) {
  const makeNode = () => ({ pass: 0, end: 0, children: new Map() });
  const root = makeNode();
  const results = [];
  for (const [action, word] of operations) {
    if (action === "add") {
      let node = root;
      node.pass++;
      for (const ch of word) {
        if (!node.children.has(ch)) node.children.set(ch, makeNode());
        node = node.children.get(ch);
        node.pass++;
      }
      node.end++;
    } else if (action === "remove") {
      let node = root;
      const path = [root];
      let found = true;
      for (const ch of word) {
        if (!node.children.has(ch)) { found = false; break; }
        node = node.children.get(ch);
        path.push(node);
      }
      if (!found || node.end === 0) continue;
      node.end--;
      for (const item of path) item.pass--;
      // Prune zero-count branches; no remaining word can use them.
      node = root;
      for (const ch of word) {
        const child = node.children.get(ch);
        if (child.pass === 0) { node.children.delete(ch); break; }
        node = child;
      }
    } else if (action === "count") {
      let node = root;
      for (const ch of word) {
        node = node.children.get(ch);
        if (!node) break;
      }
      results.push(node ? node.pass : 0);
    } else {
      throw new Error(`Unknown action: ${action}`);
    }
  }
  return results;
}
module.exports = { processPrefixOperations };
