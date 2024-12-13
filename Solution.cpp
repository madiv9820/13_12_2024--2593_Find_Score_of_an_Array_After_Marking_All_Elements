#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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

int main() {
    vector<vector<int>> nums = {{2,1,3,4,5,2},{2,3,5,1,3,2}}; vector<long long> outputs = {7,5};
    Solution sol;
    for(int index = 0; index < nums.size(); ++index) 
        cout << ((sol.findScore(nums[index]) == outputs[index]) ? "true":"false") << endl; 
}