- ## Approach 3:- Heap

    - ### Intuition:
        The problem requires us to maximize the total score by selecting elements from the array. However, once an element is selected, its adjacent elements cannot be selected again. The challenge is to find an efficient way to select elements in the optimal order while ensuring that we track which elements are already processed.

        To achieve this, we:
        1. Sort the elements in increasing order (this ensures that we start with the smallest unprocessed elements).
        2. For each element, check if it has already been processed. If it hasn't, we add its value to the score and mark it as processed.
        3. Additionally, when processing an element, we mark its adjacent elements as processed to prevent them from being selected in future iterations.

        We use a **min-heap** (priority queue) to efficiently fetch the smallest unmarked element at each step, ensuring that we always process the smallest available element first.

    - ### Approach:
        1. **Pairing Values with Indices**:
            - We pair each element with its index to keep track of the original positions in the array. This is crucial because after sorting, we still need to know the original position of each element to mark its neighbors.

        2. **Min-Heap**:
            - We use a **min-heap** to store the `(value, index)` pairs. The heap ensures that the smallest element is always at the top, making it easy to process the smallest unmarked element efficiently.
        
        3. **Marking Processed Elements**:
            - We maintain a `is_marked` vector to track whether each element has been processed. If an element is marked, we skip it.
            - When an element is processed, we mark it and also mark its adjacent elements (if they are unmarked) to ensure they aren't processed again.

        4. **Score Accumulation**:
            - Each time we process an element, we add its value to the `total_score`. We continue this process until all elements are processed.

        5. **Termination**:
            - The loop continues until all elements are processed, and the total accumulated score is returned.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
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
            ```
        
        - **C++ Solution**
            ```cpp []
            class Solution {
            public:
                long long findScore(vector<int>& nums) {
                    // Initialize the total score to 0
                    long long total_score = 0;

                    // Get the size of the nums vector
                    int n = nums.size();

                    // Create a boolean vector to track whether an element has been marked (processed)
                    vector<bool> is_marked(n, false);

                    // Create a priority queue (min-heap) to store elements (num, index) in ascending order based on num
                    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> heap;

                    // Populate the heap with (value, index) pairs from the nums vector
                    for(int index = 0; index < n; ++index) {
                        heap.push({nums[index], index});
                    }

                    // While there are elements in the heap, continue processing
                    while(heap.size()) {
                        // Get the smallest element (num, index) from the top of the heap
                        pair<int,int> p = heap.top();
                        heap.pop();

                        int num = p.first;  // The value of the current element
                        int index = p.second;  // The index of the current element

                        // If this element is already marked, skip it
                        if(is_marked[index]) continue;

                        // Add the current element's value to the total score
                        total_score += num;

                        // Mark the current element as processed
                        is_marked[index] = true;

                        // Mark the previous element (if it exists and is unmarked)
                        if(index - 1 >= 0 && !is_marked[index - 1]) is_marked[index - 1] = true;

                        // Mark the next element (if it exists and is unmarked)
                        if(index + 1 < n && !is_marked[index + 1]) is_marked[index + 1] = true;
                    }

                    // Return the accumulated total score
                    return total_score;
                }
            };
            ```

    - ### Time Complexity:
        - **Heap Operations**: Inserting an element into the heap and removing an element from the heap both take **$O(log(n))$** time. We perform these operations for each element in the array.
        - **Overall Complexity**: We perform **$n$** heap operations (one for each element), each taking **$O(log(n))$** time. Thus, the overall time complexity is **$O(n*log(n))$**.

    - ### Space Complexity:
        - **Heap**: The heap stores **$n$** elements (each pair of value and index), so it requires **$O(n)$** space.
        - **Marking Array**: The `is_marked` vector also requires **$O(n)$** space to keep track of which elements have been processed.
        - **Overall Space Complexity**: The total space complexity is **$O(n)$** due to the storage used by the heap and the marking array.