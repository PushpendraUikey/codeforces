#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1091
/*
In C++, whenever you need a collection that stays sorted, allows duplicates, and lets you delete elements 
quickly in the middle, you should use std::multiset.
A multiset handles all the shifting and sorting internally using a balanced binary search tree (Red-Black Tree). 
Deleting an element and searching for an element both take $O(\log N)$ time!
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=-1, m=-1;
    if(!(cin>>n>>m)) return 0;
    multiset<int> tickets;
    int val=-1;
    for(int i=0; i<n; i++) {
        cin >> val;
        tickets.insert(val);
    }
    for (int i=0; i<m; i++) {
        cin >> val;
        auto it = tickets.upper_bound(val);

        if(it == tickets.begin()) {
            cout << -1 << '\n';
        } else {
            it--;
            cout << *it << '\n';
            tickets.erase(it);
        }
    }
}
/*
// The code below has incorrect logic of using binary search over the non sorted array since we're updating the 
// array elements from valid values to -1 but still using the upper bound thing.
int n=-1, m=-1;
int tickets[200005];
int customer[200005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n>>m)) return 0;
    for (int i=0; i<n; i++) cin >> tickets[i];
    for (int j=0; j<m; j++) cin >> customer[j];
    unordered_map<int, int> mp;
    sort(tickets, tickets+n);

    for (int i=0; i<m; i++) {
        int indx = (upper_bound(tickets, tickets+n, customer[i]) - tickets) - 1;
        if(mp.find(indx) != mp.end()){
            int curridx = mp[indx];
            bool allocated = false;
            while(curridx>=0) {
                if(tickets[curridx] == -1) curridx--;
                else {
                    allocated = true;
                    cout << tickets[curridx] << '\n';
                    tickets[curridx] = -1;
                    curridx--;
                    break;
                }
            }
            if(!allocated) {
                cout << -1 << '\n';
            }
            mp[indx] = curridx;
        } else {
            int curridx = indx;
            bool allocated = false;
            while(indx >= 0){
                if(tickets[indx]==-1) indx--;
                else{
                    allocated = true;
                    cout << tickets[indx] << '\n';
                    tickets[indx] = -1;
                    indx--;
                    break;
                }
            }
            if(!allocated) {
                cout << -1 << '\n';
            }
            mp[curridx] = indx;
        }
    }
}
*/