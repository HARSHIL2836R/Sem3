#include<bits/stdc++.h>
using namespace std;
class comp_by_second{
    bool operator()(const pair<int,int>& a, pair<int,int>& b){
        return a.second <= b.second;
    }
};
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res(nums.size() - k + 1, 0);
        priority_queue<pair<int, int>, vector<pair<int,int>>, comp_by_second> pq;
        for (vector<int>::iterator i = nums.begin(); i != nums.end(); ++i) {
            pq.push({int(i-nums.begin()), *i});
        }
        while (pq.size() > 0) {
            int max = pq.top().second;
            int max_idx = pq.top().first;
            for (int i = max_idx - k + 1; i < max_idx + k - 1; ++i) {
                if (nums[i] )
            }
        }
    }
};