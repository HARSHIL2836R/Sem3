#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // Monotinically Decreasing (with respect to elements, not indices) Queue of indices of elements
        vector<int> ans; // The Required array
        for (int i=0; i<nums.size(); i++) { // Ending index of the window
            if (!dq.empty() && dq.front() == i-k) dq.pop_front(); // Remove the indices of outdated elements if they are in the deque
            while (!dq.empty() && nums[dq.back()] < nums[i]) // Ensure that the dp is monotonically decreasing
                dq.pop_back();
            dq.push_back(i); // Add the index at end
            if (i>=k-1) ans.push_back(nums[dq.front()]);// Add the element when the window is complete
        }
        return ans;
    }
};