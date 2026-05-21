#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://cses.fi/problemset/task/1141

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> songs(n);
    for(int i=0; i<n; i++) cin >> songs[i];

    unordered_map<int, int, custom_hash> mp;
    int left=0, right = 0;
    int maxlong = 0;
    int lastrepeatedindx = 0;
    while(right < n) {
        int cursong = songs[right];
        if(mp.count(cursong) > 0) {
            maxlong = max(maxlong, right - left);
            left = max(left, mp[cursong]+1);        // for cases such as: 2 2 1 1 2 1 2 1 2 1, left may incorrectly fall back
        }
        mp[cursong] = right;
        right++;
    }
    maxlong = max(maxlong, right - left);
    cout << maxlong << '\n';
}
// Two pointer problem with correct conditions and correct wrap up logic.