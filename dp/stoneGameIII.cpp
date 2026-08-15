#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        string stoneGameIII(vector<int>& stoneValue) {
            int n = stoneValue.size();
            // dp[i] represents the max relative score difference starting at index i
            // Since we need only 3 states, we use 3 variables instead of an array.
            // iplus1 represents dp[i+1], iplus2 represents dp[i+2], iplus3 represents dp[i+3]
            int iplus1 = 0, iplus2 = 0, iplus3 = 0;
            for(int i=n-1; i>=0; i--) {
                int current_dp = -1e9; // Initialize to a very small number
                int take = 0;
                // Try picking 1, 2, or 3 stones
                for(int j=0; j<3 && i+j<n; j++) {
                    take += stoneValue[i+j];

                    // subtract opponent's best possible relative score from the remaining array.
                    int opponent_score = (j == 0) ? iplus1 : (j == 1) ? iplus2 : iplus3;
                    current_dp = max(current_dp, take - opponent_score);
                }

                iplus3 = iplus2;
                iplus2 = iplus1;
                iplus1 = current_dp;
            }

            if(iplus1 > 0) return "Alice";
            else if(iplus1 < 0) return "Bob";
            else return "Tie";
        }
};