#include <bits/stdc++.h>
using namespace std;
// https://cses.fi/problemset/task/1084

int n=-1, m=-1, k=-1;
int appl[200005];
int apar[200005];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n>>m>>k)) return 0;
    for (int i=0; i<n; i++) cin >> appl[i];
    for (int j=0; j<m; j++) cin >> apar[j];
    sort(appl, appl+n);
    sort(apar, apar+m);

    int allocApart=0;
    int i=0, j=0;
    while(i<n && j<m) {
        int currappl = appl[i];
        int currapar = apar[j];
        if(currapar >= currappl-k && currapar <= currappl+k) {
            allocApart++;
            j++;
            i++;
        }else if(currappl > currapar) {
            j++;
        }else {
            i++;
        }
    }
    cout << allocApart << '\n';
}