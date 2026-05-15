#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
You are given a 0-indexed integer array nums. You are allowed to permute 
nums into a new array perm of your choosing.

We define the greatness of nums be the number of indices 
0 <= i < nums.length for which perm[i] > nums[i].

Return the maximum possible greatness you can achieve after permuting nums.
*/

class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int totalscore = 0;
        int left = 0;
        int right = 0;
        while(right < nums.size()) {
            if(nums[right] > nums[left]) {
                totalscore++;
                right++;
                left++;
            }
            else {
                right++;
            }
        }
        return totalscore;
    }
};