#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int removeDuplicates(vector<int>& arr) {
        int size = arr.size();
        int right = 0;
        int left = 0;
        int lastcnt = 0;
        int shrink = 0;

        while(right < size-1) {
            if(arr[right] == arr[right+1]) {
                lastcnt++;
                if(lastcnt > 1) {
                    shrink++;
                } else{
                    left++;
                }
                right++;
            } else{
                lastcnt=0;
                right++;
                left++;
            }
            int t = arr[left];
            arr[left] = arr[right];
            arr[right] = t;
        }
        int t = arr[left];
        arr[left] = arr[right];
        arr[right] = t;

        return size-shrink;
    }
};