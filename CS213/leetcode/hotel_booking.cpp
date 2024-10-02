#include <bits/stdc++.h>
using namespace std;
class MyCalendarTwo {
public:
    vector<pair<int,int>> one_fill;
    vector<pair<int,int>> full;
    MyCalendarTwo() {
    }
    
    bool book(int start, int end) {
        bool check_full = false;
        for (auto itr: one_fill){
            if (itr.first >= start && itr.first < end) {
                check_full = true;
                itr.second = itr.second > end ? end: itr.second;
            }
            else if (itr.second >= start && itr.second < end) {
                check_full = true;
            }
        }
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */