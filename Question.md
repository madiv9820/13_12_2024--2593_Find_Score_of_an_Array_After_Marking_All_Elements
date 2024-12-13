# [2593. Find Score of an Array After Marking All Elements](https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements?envType=daily-question&envId=2024-12-13)

**Type:** Medium <br>
**Topics:** Heap (Priority Queue), Sorting, Array, Simulation, Hash Table <br>
**Companies:** Visa
<hr>

You are given an array `nums` consisting of positive integers.

Starting with `score = 0`, apply the following algorithm:

- Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
- Add the value of the chosen integer to `score`.
- Mark **the chosen element and its two adjacent elements if they exist.**
- Repeat until all the array elements are marked.

Return *the score you get after applying the above algorithm*.
<hr>

### Examples:

- **Example 1:** <br>
**Input:** nums = [2,1,3,4,5,2] <br>
**Output:** 7 <br>
**Explanation:** We mark the elements as follows: <br> - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2]. <br> - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2]. <br> - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2]. <br> Our score is 1 + 2 + 4 = 7.

- **Example 2:** <br>
**Input:** nums = [2,3,5,1,3,2] <br>
**Output:** 5 <br>
**Explanation:** We mark the elements as follows: <br> - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2]. <br> - 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2]. <br> - 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2]. <br> Our score is 1 + 2 + 2 = 5.
<hr>

### Constraints:
- <code>1 <= nums.length <= 10<sup>5</sup></code>
- <code>1 <= nums[i] <= 10<sup>6</sup></code>

### Hints
- Try simulating the process of marking the elements and their adjacent.
- If there is an element that was already marked, then you skip it.