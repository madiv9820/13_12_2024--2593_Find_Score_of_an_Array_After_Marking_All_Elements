#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

int main() {
    vector<vector<int>> nums = {{2,1,3,4,5,2},{2,3,5,1,3,2}}; vector<long long> outputs = {7,5};
    Solution sol;
    for(int index = 0; index < nums.size(); ++index) 
        cout << ((sol.findScore(nums[index]) == outputs[index]) ? "true":"false") << endl;
}