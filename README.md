## Approach 2:- Sorting

- ### Intuition:
    The goal of the problem is to maximize the total score by selecting elements from an array, but with the restriction that when an element is selected, its adjacent neighbors are also marked and cannot be selected again. 

    To achieve this:

    1. We need to choose elements starting with the smallest unmarked element.
    2. Once an element is selected, both the element and its immediate neighbors (if unmarked) are marked.
    3. The score is accumulated by adding the value of the selected element in each iteration.

- ### Approach:
    1. **Pairing Values with Indices**:
        - We first create a vector of pairs, where each pair consists of an element from the array and its original index. This allows us to keep track of the indices even after sorting the values.

    2. **Sorting**:
        - We sort the array based on the element values. If there are duplicate values, the sorting ensures that we process them in their original order, as the index is used as a tiebreaker.
    
    3. **Processing Elements**:
        - We then iterate through the sorted array of pairs and select the smallest unmarked element. We add its value to the total score and mark it as processed.
        - We also mark its immediate neighbors (left and right, if they exist and are unmarked) as processed to ensure they cannot be selected in future iterations.

    4. **Termination**:
        - The loop continues until all elements are processed, and the accumulated total score is returned.

- ### Code Implementation
    - **Python Solution**
        ```python3 []
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
        ```
    
    - **C++ Solution**
        ```cpp []
        class Solution {
        public:
            long long findScore(vector<int>& nums) {
                // Get the size of the input array 'nums'
                int n = nums.size();
                
                // Create a vector of pairs to store each element and its index
                vector<pair<int,int>> nums_With_Index(n);
                
                // Create a boolean vector to track if an element has been marked (processed)
                vector<bool> is_marked(n, false);
                
                // Initialize the total score to 0
                long long total_score = 0;

                // Populate the nums_With_Index vector with pairs of (num, index)
                for(int index = 0; index < n; ++index) 
                    nums_With_Index[index] = {nums[index], index};  // Pairing the value with its original index
                
                // Sort the vector of pairs by the first element (value), and in case of ties, by the second element (index)
                // This will process the smallest numbers first, and for equal numbers, in the order of their original indices
                sort(nums_With_Index.begin(), nums_With_Index.end());
                
                // Iterate through the sorted list of (value, index) pairs
                for(const pair<int,int>& p: nums_With_Index) {
                    // Extract the value (num) and its original index
                    int num = p.first, index = p.second;
                    
                    // If this element has already been marked, skip it
                    if(is_marked[index]) continue;

                    // Add the value to the total score as it's the smallest unmarked number
                    total_score += num;
                    
                    // Mark the current element as processed
                    is_marked[index] = true;

                    // If the previous element exists and is unmarked, mark it as processed
                    if(index - 1 >= 0 && !is_marked[index - 1]) is_marked[index - 1] = true;

                    // If the next element exists and is unmarked, mark it as processed
                    if(index + 1 < n && !is_marked[index + 1]) is_marked[index + 1] = true;
                }

                // Return the accumulated total score
                return total_score;
            }
        };
        ```

- ### Time Complexity:
    The time complexity of the approach is dominated by the sorting step. Here's the breakdown:

    - **Sorting** the array of pairs takes **$O(n * log(n))$** time.
    - After sorting, we iterate through the array once to process each element, which takes **$O(n)$** time.

    Thus, the overall time complexity is **$O(n * log(n))$**, where `n` is the length of the input array `nums`.

- ### Space Complexity:
    The space complexity is determined by the additional storage we use:

    - **Vector for Pairs (`nums_With_Index`)**: We create a vector of size `n` to store pairs of (value, index), so it requires **$O(n)$** space.
    - **Boolean Vector (`is_marked`)**: We create a boolean vector of size `n` to track which elements have been marked, requiring **$O(n)$** space.

    Therefore, the overall space complexity is **$O(n)$**.