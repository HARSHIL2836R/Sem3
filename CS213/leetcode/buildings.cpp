#include <vector>
#include "heap.h"
using namespace std;
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Heap> x;
        for (vector<vector<int>>::iterator curr_building = buildings.begin(); curr_building != buildings.end(); curr_building++) {
            for (int i = (*curr_building)[0]; i <= (*curr_building)[1]; i++) {
            while (x.size()<i+3){
                Heap a;
                x.push_back(a);
            }
            x[i].insert((*curr_building)[2]);
            }
        }
        vector<int> heights;
        for (vector<Heap>::iterator curr_heap = x.begin(); curr_heap != x.end(); curr_heap++) {
            if ((*curr_heap).size() == 0){
                heights.push_back(0);
                continue;
            }
            heights.push_back((*curr_heap).max());
        }
        vector<int>::iterator itr = heights.begin();
        vector<vector<int>> result;
        bool get_zero = false;
        while (itr!= heights.end()){
            if (*itr == 0 && get_zero == false){
                advance(itr,1);
                continue;
            }
            else{
                if (result.size()>0 && *itr == (result.back())[1]){
                    advance(itr,1);
                    continue;
                }
                else{
                    get_zero = true;
                    if (*itr<*(itr-1)){
                        result.push_back({int(itr-heights.begin())-1,*itr});
                    }
                    else{
                        result.push_back({int(itr-heights.begin()),*itr});
                    }
                    advance(itr,1);
                }
            }
        }
        return result;
    }
};
int main(){
    Solution s;
    vector<vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    s.getSkyline(buildings);
    return 0;
}