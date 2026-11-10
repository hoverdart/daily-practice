# Attempt — Count Affordable Mixed-Channel Bursts

Fill out before opening reference/.

- Start / finish / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute force time and space:
- Optimal expected time and auxiliary space:
- First failing case / hint / Java Map syntax:

## Recognition / core invariant

- Which phrases indicate an expanding-and-shrinking **contiguous** window?
- Why is the condition monotone when removing a value from the left?
- What does freq.get(channelId) count? Why remove keys at frequency zero?
- What precisely does runningCost represent?
- Why must the shrink loop use OR, not AND, between the two violations?
- For each fixed right, why are there exactly right-left+1 legal starts?
- Why does the result need long, even if the input length fits int?
- What if maxDistinct = 0, cost is zero, or IDs are negative?
- Invent a case where an early long sum overflows int.
- Why do signed **negative** costs invalidate this specific sliding-window reasoning?

## CS61B / Java

- How do HashMap getOrDefault, put, size, and remove work?
- Why is the expected total O(n) despite the nested while?
- If hash-map operations could be adversarially slow, which runtime qualifier changes?
- What feedback should the next practice session use?
