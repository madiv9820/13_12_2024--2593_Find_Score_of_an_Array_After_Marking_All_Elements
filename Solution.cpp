#include <iostream>
#include <vector>
#include <limits>
using namespace std;

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

int main() {
    vector<vector<int>> nums = {{2,1,3,4,5,2},{2,3,5,1,3,2}}; vector<long long> outputs = {7,5};
    Solution sol;
    for(int index = 0; index < nums.size(); ++index) 
        cout << ((sol.findScore(nums[index]) == outputs[index]) ? "true":"false") << endl; 
}