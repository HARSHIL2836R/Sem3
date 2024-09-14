#include <bits/stdc++.h>
using namespace std;
class MedianFinder {
public:
    //https://leetcode.com/problems/find-median-from-data-stream/solutions/1330646/c-java-python-minheap-maxheap-solution-picture-explain-clean-concise
    priority_queue<int> maxHeap; // Heap to store the larger numbers in the stream(not chronologically)
    priority_queue<int, vector<int>, greater<int>> minHeap; // Heap to store the smaller numbers in the stream(not chronologically)
    
    MedianFinder() {
    }
    void addNum(int num) {
        maxHeap.push(num); // Assume number is large
        minHeap.push(maxHeap.top()); // Reduce the size of maxHeap
        maxHeap.pop(); // Could have been optimized by not using multiple push pop operations
        if (minHeap.size() > maxHeap.size()) { // Balance heaps, could have been other way round too
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top(); // odd number of elements
        return (maxHeap.top() + minHeap.top()) / 2.0; // even number of elements
    }
};