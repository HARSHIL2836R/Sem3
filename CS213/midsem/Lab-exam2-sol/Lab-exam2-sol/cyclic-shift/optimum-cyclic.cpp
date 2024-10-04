/*

Solution by double hashing the prefixes

Time Complexity: O(n) always
Auxillary Space Complexity: O(1)

*/


#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, n) for(int i = 0; i < n; i++)

#define watch(x) ;// cerr<<(#x)<<" is "<<x<<"\n";

const int M1 = 1e9 + 9;
const int B1 = 37;

const int M2 = 1e9 + 7;
const int B2 = 41;

int inv(int a, int M) {
  return a <= 1 ? a : M - (long long)(M/a) * inv(M % a, M) % M;
}

int cyclic_shifts(string s){

    int n = s.length();

    int full_hash1 = 0, full_hash2 = 0;
    int Bn1 = 1, Bn2 = 1;

    rep(i, n){
        full_hash1 = (full_hash1*B1 + M1)%M1;
        full_hash1 = (full_hash1 + s[i])%M1;

        full_hash2 = (full_hash2*B2 + M2)%M2;
        full_hash2 = (full_hash2 + s[i])%M2;

        Bn1 = (Bn1*B1 + M1)%M1;
        Bn2 = (Bn2*B2 + M2)%M2;
    }

    watch(full_hash1);
    watch(full_hash2);
    watch(Bn1);
    watch(Bn1);

    int k;
    int prefix_hash1 = 0, prefix_hash2 = 0;
    int Bi1 = 1, Bi2 = 1;
    int temp_hash1, temp_hash2;

    for(int i = 1; i <= n; i++){
        prefix_hash1 = (prefix_hash1*B1 + M1)%M1;
        prefix_hash1 = (prefix_hash1 + s[i-1])%M1;

        prefix_hash2 = (prefix_hash2*B2 + M2)%M2;
        prefix_hash2 = (prefix_hash2 + s[i-1])%M2;

        watch(prefix_hash1);
        watch(prefix_hash2);

        Bi1 = (Bi1*B1 + M1)%M1;
        Bi2 = (Bi2*B2 + M2)%M2;

        watch(Bi1);
        watch(Bi2);

        if(n%i == 0){
            k = n/i;

            // (B^(ki) - 1)/(B^i - 1)
            temp_hash1 = (prefix_hash1*(Bn1 - 1) + M1)%M1;
            temp_hash1 = (temp_hash1*inv(Bi1 - 1, M1) + M1)%M1;

            temp_hash2 = (prefix_hash2*(Bn2 - 1) + M2)%M2;
            temp_hash2 = (temp_hash2*inv(Bi2 - 1, M2) + M2)%M2;

            if((temp_hash1 == full_hash1) && (temp_hash2 == full_hash2)){
                return k;
            }
        }
    }

    return 1;
}

