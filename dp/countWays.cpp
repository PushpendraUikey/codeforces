#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007

/*-------- Classic DP + Integer Partition --------*/

// Number of ways to write `n` as a sum of two positive integers
int countWays(int n){
    vector<vector<int>> dp(n, vector<int>(n+1, 0));

    // dp[i][j] ---> ways to form sum `j` using 1...i coins
    for(int i=0; i<n ; i++ ) {
        dp[i][0] = 1;   // ways to form 0 using 1...i
    }

    for(int i=1; i<n; i++){
        for(int j=1; j<=n; j++){
            dp[i][j] = dp[i-1][j];
            if(j>=i){
                dp[i][j] = (dp[i][j]+dp[i][j-i])%mod;
            }
        }
    }

    return dp[n-1][n]; // ways to form n using 1...n-1 coins
}

int countWays(int n){
    vector<int> dp(n+1, 0);
    dp[0] = 1;  // number of ways to make a zero

    // the table is only gonna be filled in bottom up
    for(int num=1; num<=n; num++){
        for(int sum=num; sum<=n; sum++){
            // If we want to build sum,
            // we can add num to all ways of forming sum - num.
            dp[sum] = (dp[sum]+dp[sum-num])%mod;
        }
    }

    return dp[n]-1; // subtract 1 to exclude the case where n is formed by itself
}