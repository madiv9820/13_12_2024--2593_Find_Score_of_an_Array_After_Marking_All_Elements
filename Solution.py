from typing import List

class Solution:
    def findScore(self, nums: List[int]) -> int:
        total_score = 0  # Initialize total score to 0
        n = len(nums)  # Get the length of the list
        is_marked = [False] * n  # List to track which elements are marked
        marked_count = 0  # Counter to keep track of how many elements are marked

        # Loop until all elements are marked
        while marked_count < n:
            min_value = float('inf')  # Initialize to infinity to find the minimum value
            min_index = -1  # Variable to store the index of the minimum value

            # Find the unmarked element with the minimum value
            for i in range(n):
                if not is_marked[i] and nums[i] < min_value:
                    min_value, min_index = nums[i], i

            # If no unmarked elements left, break out of the loop (this shouldn't happen)
            if min_value == float('inf'):
                break

            # Add the minimum value to the total score
            total_score += min_value

            # Mark the current element as processed
            is_marked[min_index] = True
            marked_count += 1

            # Mark the previous element if it exists and is unmarked
            if min_index - 1 >= 0 and not is_marked[min_index - 1]:
                is_marked[min_index - 1] = True
                marked_count += 1

            # Mark the next element if it exists and is unmarked
            if min_index + 1 < n and not is_marked[min_index + 1]:
                is_marked[min_index + 1] = True
                marked_count += 1

        return total_score  # Return the accumulated total score