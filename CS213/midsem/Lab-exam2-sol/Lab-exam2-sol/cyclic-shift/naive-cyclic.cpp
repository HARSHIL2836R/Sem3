/*

Naive solution but optimized by reducing the problem

Time Complexity: O(n^2) worst case on highly composite string lengths
Auxillary Space Complexity: O(n)

*/


#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)
#define watch(x) cerr<<(#x)<<" is "<<x<<"\n";

int cyclic_shifts(string s){

    int n = s.length(), k;
    bool match;
    string p;

    for(int i = 1; i <= n; i++){
    	if(n%i == 0){
    		k = n/i;

    		p = s.substr(0, i);

    		match = 1;
    		rep(j,k){
                //num_calls += i;
    			match &= (s.substr(j*i, i) == p);
                if(!match) break;
    		}

    		if(match) return k;
    	}
    }

    return 1;
}

