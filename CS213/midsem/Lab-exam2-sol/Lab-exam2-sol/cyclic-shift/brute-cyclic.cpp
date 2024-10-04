/*

Complete brute force by directly generating strings

Time Complexity: O(n^2) always
Auxillary Space Complexity: O(n)

*/


#include <bits/stdc++.h>
using namespace std;


long long cyclic_shifts(string s){

    // Complete this function

    int n = s.length();

    int ans = 0;

    string t;

    for(int i = 0; i < n; i++){
      t = s.substr(i, n-i) + s.substr(0, i);
      ans += (t == s);
    }

    // Return the number of integers k
    return ans;
}

