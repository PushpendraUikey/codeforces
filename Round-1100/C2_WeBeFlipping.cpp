#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int arr[200005];
void solve() {
    int n;  cin >> n;

    for(int i=0; i<n; i++) cin >> arr[i];

    vector<ll> pref(n), suff(n+1);
    pref[0] = abs(arr[0]);
    for(int i=1; i<n; i++) pref[i] = pref[i-1] + abs(arr[i]);

    suff[n-1] = arr[n-1]; suff[n] = 0;
    for(int i=n-1; i>=0; i--) suff[i] = suff[i+1] + arr[i];

    // Selecting the optimal indx to operate on so as to maximize the output
    int indx = -1;
    ll best = suff[0];
    for(int i=1; i<n; i++){
        if(arr[i] > 0) {
            ll score = pref[i-1] + suff[i+1] - arr[i];
            if(score > best) {
                best = score;
                indx = i;
            }
        }
    }

    if(indx == -1) {
        cout << "0\n";
        return;
    }

    // negating all the index before `indx` to flip the value at indx and values before it will be pos and val at indx will be neg
    int par = 0;
    vector<int> ans;
    for (int i=indx-1; i>=0; i--) {
        if(par == 1){
            arr[i] = -arr[i];
        }
        if(arr[i] > 0) {
            ans.push_back(i+1);
            par = par^1;
        }
    }
    ans.push_back(indx+1);

    cout << ans.size() << '\n';
    for(int i=0; i<ans.size(); i++) {
        cout << ans[i] << ' '; 
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while(tt-->0) solve();
}