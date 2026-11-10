# Evacuate the Flooded Relay Station (Hard / Stretch)

A relay station floor plan is a rectangular grid. All moves take exactly **one minute** and go up, down, left, or right. The grid contains:

- '#' = wall, impassable to both people and flood
- '.' = open tile
- 'S' = your starting tile (exactly one)
- 'E' = the exit tile (exactly one)
- 'F' = a flood source, initially flooded at minute 0 (there may be none)
- 'G' = a gated tile

**Flood behavior:** At the end of each minute, the flood spreads simultaneously from all flooded tiles to all orthogonally adjacent **non-wall** tiles, including gates, S, and E. Once flooded, a tile remains flooded.

**Human behavior:** Starting at S at minute 0, you must move exactly one tile per minute (waiting never improves safety). You may enter a G tile **at most once over the entire route** using a one-use gate permit; all other G entries would be illegal. Every entered tile, including E, must be **not yet flooded at the minute you arrive**. Flood spreading and a human step occur concurrently during a minute, so **arrival at the exact minute a tile floods is not safe**. You may depart a tile as flood reaches it, provided your new tile is still safe upon arrival. Gates do not slow or block the flood.

Return the minimum safe number of minutes to reach E, or -1 if impossible.

~~~java
public static int minimumEscapeMinutes(char[][] grid)
~~~

Examples:

~~~text
["S.G.E"]      => 4    // one gate entry
["S.G.GE"]     => -1   // two gate entries required in the only corridor
["S.E",
 "F##"]       => 2    // flood reaches E at minute 3, after arrival at minute 2
["S.E",
 "..F"]       => -1   // flood reaches E at minute 1, before arrival
~~~

Constraints: 1 <= rows, cols <= 350 and rows*cols <= 120_000; exactly one S and one E, different tiles; any number of F and G cells. No mutation of grid. Target O(rows*cols) time and memory.

Interview checkpoints: Why can't a single BFS from S handle the moving hazard without knowing arrival deadlines? How does a **multi-source BFS** compute each tile's flood time? Why do (r,c,permitUnused) and (r,c,permitUsed) need separate visited states? What strict inequality must hold before enqueueing?
