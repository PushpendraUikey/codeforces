#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Just trying to convert each of array element to negative by flipping to minimize the sum
// We have enough number of operations to flip all elements.

int arr[200005];
void solve() {
    int n;  cin >> n;

    for(int i=0; i<n; i++) cin >> arr[i];

    int neg=0;
    queue<int> q;

    for(int i=n-1; i>=0; i--) {
        if(arr[i] > 0 && neg%2==0){
            neg++;
            q.push(i+1);
        }
        else if(arr[i] < 0 && neg%2==1){ // This will happen only after some positive val in original array was flipped
            neg++;
            q.push(i+1);
        }
    }

    cout << neg << '\n';
    while(!q.empty()){
        cout << q.front() << ' ';
        q.pop();
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