def longest_stable_window(readings: list[int], k: int) -> int:
    """Return the maximum length of a contiguous window with <= k distinct codes."""
    counts = {}
    maxLength = 0
    left=0
    right=0
    while right < len(readings):
        counts[readings[right]] = counts.get(readings[right], 0) + 1 #adds the current reading to the counts dictionary, incrementing its count if it already exists or initializing it to 1 if it doesn't.
        while len(counts) > k: #OH, I get it now! counts is a dictionary that keeps track of how many distinct readings are in the current window. Each key is a distinct reading, and the value is how many times that reading appears in the current window. So, if len(counts) > k, that means we have more than k distinct readings in the current window, and we need to shrink the window from the left until we have <= k distinct readings. Neat! 
            counts[readings[left]] -= 1 #guaranteed to exist 
            if counts[readings[left]] == 0:
                del counts[readings[left]] #so we don't accidentally delete smth else?
            left += 1
        maxLength = max(maxLength, right - left + 1)
        right += 1
    return maxLength




# FAILED APPROACH: I tried to use a set to keep track of distinct items, but that doesn't work because I need to know how many of each item are in the window. So I need a dictionary to keep track of counts.
# maxLength = 0
# currLength = 0
# currDistinct = set()
# for eachInt in readings:
#     currDistinct.add(eachInt)
#     if len(currDistinct) <= k and k != 0:
#         currLength +=1 
#     else:
#         currDistinct.clear()
#         currDistinct.add(eachInt)
#         currLength = 1
#     maxLength = max(maxLength, currLength)

# return maxLength