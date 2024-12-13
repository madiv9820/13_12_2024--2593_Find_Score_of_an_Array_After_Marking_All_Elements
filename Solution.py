from typing import List
import heapq

class Solution:
    def findScore(self, nums: List[int]) -> int:
        # Get the length of the nums array
        n = len(nums)
        
        # Create a list of tuples (num, index) where each tuple is a value from 'nums' and its corresponding index
        nums_With_Index = [(num, index) for index, num in enumerate(nums)]
        
        # Initialize a list to track whether each element has been marked (True means marked)
        is_marked = [False] * n
        
        # Initialize total_score to 0 to accumulate the sum of selected elements
        total_score = 0
        
        # Convert the list into a heap (min-heap), which will allow us to efficiently pop the smallest element
        heapq.heapify(nums_With_Index)
        
        # While there are elements in the heap, continue the process
        while len(nums_With_Index):
            # Pop the smallest element from the heap (which is a tuple of num and index)
            num, index = heapq.heappop(nums_With_Index)
            
            # If the current element is already marked, skip it
            if is_marked[index]: continue

            # Add the value of the selected number to the total score
            total_score += num
            
            # Mark the current element as processed
            is_marked[index] = True

            # If the previous element exists and is unmarked, mark it as processed
            if index - 1 >= 0 and not is_marked[index - 1]: is_marked[index - 1] = True

            # If the next element exists and is unmarked, mark it as processed
            if index + 1 < n and not is_marked[index + 1]: is_marked[index + 1] = True
        
        # Return the accumulated total score after processing all elements
        return total_score