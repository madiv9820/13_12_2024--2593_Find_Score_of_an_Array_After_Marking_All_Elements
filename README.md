# Find Score of an Array After Marking All Elements (All Approaches)
- ## Approach 1:- Linear Search (Time Limit Exceed)
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

- ## Approach 2:- Sorting
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