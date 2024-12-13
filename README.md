- ## Approach 1:- Brute Force
    - ### Intuition:
        The problem involves selecting elements from an array based on a special scoring system where:

        1. In each step, we select the minimum unmarked element in the array.
        2. After selecting this minimum element, we mark it and its adjacent neighbors as processed (or "marked").
        3. The score is accumulated by adding the value of the selected minimum element in each step.

        The goal is to maximize the total score by strategically selecting these elements while ensuring that their neighbors are also marked and won't be available for future selections.

    - ### Approach:
        1. **Initialization**:
            - We initialize a `total_score` variable to 0 to accumulate the score.
            - We maintain a boolean vector `is_marked` of the same length as the input array, `nums`, which tracks whether an element is marked (processed) or not.
            - We also keep a counter, `marked_count`, to track how many elements have been marked.

        2. **Main Loop**:
            - While there are still unmarked elements (i.e., `marked_count < n`), we search for the unmarked element with the smallest value.
            - This is done by iterating through the `nums` array and comparing unmarked elements.
            - Once the minimum unmarked element is found, its value is added to `total_score`.
            - We then mark this element and its immediate neighbors (if they exist and are unmarked) as processed.

        3. **Marking Neighbors**:
            - After selecting an element, we check its left and right neighbors (if they exist within bounds) and mark them as processed to prevent them from being selected in future steps.

        4. **Termination**:
            - The loop stops once all elements are marked, and the accumulated `total_score` is returned as the final result.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
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
            ```
        
        - **C++ Solution**
            ```cpp []
            class Solution {
            public:
                long long findScore(vector<int>& nums) {
                    long long total_score = 0;  // Initialize total score to 0
                    int n = nums.size();  // Get the size of the nums vector
                    vector<bool> is_marked(n, false);  // Vector to track which elements are marked
                    int marked_count = 0;  // Counter to keep track of how many elements are marked

                    // Loop until all elements are marked
                    while(marked_count < n) {
                        int min_value = numeric_limits<int>::max();  // Initialize min_value to the maximum integer value
                        int min_index = -1;  // Variable to store the index of the minimum value

                        // Find the unmarked element with the minimum value
                        for(int i = 0; i < n; ++i) 
                            if(!is_marked[i] && nums[i] < min_value) { 
                                min_value = nums[i];  // Update the minimum value
                                min_index = i;        // Update the index of the minimum value
                            }
                        
                        // If no unmarked element is found, break out of the loop (this shouldn't happen)
                        if(min_index == -1) break;

                        // Add the minimum value to the total score
                        total_score += min_value;

                        // Mark the current element as processed
                        is_marked[min_index] = true;

                        // Mark the previous element if it exists and is unmarked
                        if(min_index - 1 >= 0 && !is_marked[min_index - 1]) {
                            is_marked[min_index - 1] = true;
                            marked_count++;  // Increment marked_count
                        }

                        // Mark the next element if it exists and is unmarked
                        if(min_index + 1 < n && !is_marked[min_index + 1]) {
                            is_marked[min_index + 1] = true;
                            marked_count++;  // Increment marked_count
                        }
                    }

                    return total_score;  // Return the accumulated total score
                }
            };
            ```

    - ### Time Complexity:
        The time complexity of this approach is **$O(n^2)$**, where `n` is the length of the input array `nums`. Here's the breakdown:

        - The outer `while` loop runs until all elements are marked. In the worst case, this will run `n` times.
        - Inside the loop, the algorithm searches for the minimum unmarked element, which requires scanning the entire array of size `n`. This gives an **$O(n)$** operation within the loop.
        
        Thus, in total, the time complexity is **$O(n) * O(n) = O(n^2)$**.

    - ### Space Complexity:
        The space complexity is **$O(n)$**, where `n` is the length of the input array `nums`. This space is used to store:

        - The `is_marked` vector, which tracks the marking status of each element.
        - A few integer variables like `total_score`, `min_value`, `min_index`, and `marked_count` that require constant space.

        Therefore, the space complexity is dominated by the `is_marked` vector, making it **$O(n)$**.