# Attempt Log

Fill this out **before** opening `reference/`.

- **Started:** 11:55 PM
- **Finished:** 12:13 AM
- **Time spent:** 15-20 min
- **Outcome:** `solved with hint`
- **Confidence (1-5):** 2

## My approach
My previous approach was to simply MOVE ON, after a window was deemed bad. But that wasn't what the problem was asking. 

I had to ask ChatGPT for some hints as to how to implement this. Then, it actually came to me:
- we count how many times we see each kind of number in a dictionary, incrementing it with every new number we see w/ readings.get(readings[right], 0) + 1
- Oh, and we also have left/right pointers, so [l . . r . . ] (kinda like that?)
- the confusing part for me was what to do with this counts dictionary. 

## Complexity I claimed

- Time: O(n)
- Space: O(n)

## What tripped me up?
The purpose of the dictionary here. Reading the solution finally got me to understand, though!
I've also never used "del". There's quit e abit of python syntax I need to brush up on...

## Hint(s) used


## After reading the reference

- What was different about the optimal approach?
- What pattern should I recognize next time?
- What language-specific syntax/API did I forget?
- One thing to remember:
