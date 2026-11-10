# Attempt — Evacuate the Flooded Relay Station

Complete before reading reference/.

- Start / finish / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force approach and time/space:
- Optimal time/space in R,C:
- First failed test or Java syntax friction:

## Recognition and modeling

- Identify the two separate BFS processes. What does each queue represent?
- Why is there a **single multi-source** flood BFS instead of running BFS once for each F?
- State the exact meaning of floodAt[r][c], including unreachable cells.
- Why does arrival == floodAt mean failure, not success?
- Why can the human safely leave a tile just as the flood reaches it?
- What are the two states at the same location? When is the second worth keeping?
- What happens if I stand on G and step back on a G later?
- Why doesn't a normal visited[r][c] suffice?
- Explain why earliest arrival dominates later arrival to the **same full state**.
- Why does the person need a FIFO queue rather than priority queue?
- What is the maximum number of expanded graph vertices and edges?

## CS61B / Java recall

- How are row and column encoded as an integer ID?
- How do I represent an infinity/no-flood deadline without integer overflow?
- Why must I mark a state visited when **enqueuing**, not only when dequeuing?
- List two off-by-one or boundary cases to rehearse in 2–4 days:
