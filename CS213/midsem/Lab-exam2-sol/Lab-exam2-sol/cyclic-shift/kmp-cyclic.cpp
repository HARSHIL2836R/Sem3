/*

Solution using KMP algorithm

Time Complexity: O(n) always
Auxillary Space Complexity: O(n)

*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;


class KMPAlgorithm {
public:
    // Function to compute the optimized Prefix Function of a string in O(N) time
    static vector<int> prefixFunction(const string& s) {
        int n = s.size();
        vector<int> pi(n);

        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];

            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];

            if (s[i] == s[j])
                j++;

            pi[i] = j;
        }

        return pi;
    }

    // Function to find all occurrences of pattern p in text t using KMP algorithm
    static int patternSearching(const string& t, const string& p) {
        int n = p.size(), m = t.size();
        string s = p + "#" + t;

        vector<int> pi = prefixFunction(s);
        int ans = 0;

        for (int i = n + 1; i < n + 1 + m; i++) {
            if (pi[i] == n) {
                // ans.push_back(i - 2 * n);
                ans++;
            }
        }

        return ans;
    }
};

int cyclic_shifts(string s){

    int occurrences = KMPAlgorithm::patternSearching(s + s, s) - 1;

    return occurrences;
}

