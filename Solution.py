from typing import List

class Solution:
    def findScore(self, nums: List[int]):
        # Get the length of the nums list
        n = len(nums)

        # Create a list of tuples (num, index) where 'num' is the value and 'index' is its position in the original list
        nums_With_Index = [(num, index) for index, num in enumerate(nums)]
        
        # Initialize a list to keep track of whether an element has been marked (True means marked)
        is_marked = [False] * n
        
        # Initialize the total score to 0
        total_score = 0

        # Sort the list of tuples by the number first (ascending), and by the index secondarily (also ascending)
        # This ensures we process the numbers in increasing order and, in case of ties, in their original order
        nums_With_Index.sort(key = lambda x: (x[0], x[1]))

        # Iterate through each (num, index) pair in the sorted list
        for num, index in nums_With_Index:
            # If the current number at 'index' is already marked, skip it
            if is_marked[index]: continue

            # Add the current number to the total score as it's the smallest unmarked number
            total_score += num
            
            # Mark the current element at 'index' as processed
            is_marked[index] = True
            
            # If the previous element exists and is not marked, mark it as processed
            if index - 1 >= 0 and not is_marked[index - 1]: is_marked[index - 1] = True

            # If the next element exists and is not marked, mark it as processed
            if index + 1 < n and not is_marked[index + 1]: is_marked[index + 1] = True
        
        # Return the accumulated total score
        return total_score