#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (char i: s){
            bool ok = false;
            vector<pair<char,char>> par{{'(',')'},{'[',']'},{'{','}'}};
            for (vector<pair<char,char>>::iterator j = par.begin(); j != par.end(); ++j){
                if (i == (*j).first){ 
                    stk.push((*j).first);
                    ok = true;
                    break;
                }
                if (!stk.empty() && (*j).second == i && stk.top() == (*j).first){
                    stk.pop();
                    ok = true;
                    break;
                }
            }
            if (!ok) return false;
        }
        if (stk.empty()) return true;
        else return false;
    }
};