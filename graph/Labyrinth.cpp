#include <bits/stdc++.h>
using namespace std;

// Intead of copying a large string again and again we shifted to keep the parent pointers through 
// which we can recreate the path we came along using the directions we updated in queue and 
// following the pointers along the way.
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    int sx, sy, ex, ey;
    if(!(cin>>n>>m)) return 0;
    vector<string> grid(n);
    for(int i=0; i<n; i++) {
        cin >> grid[i];
        for(int j=0; j<m; j++) {
            if(grid[i][j]=='A') {
                sx = i; sy = j;
            }
            else if(grid[i][j] == 'B') {
                ex = i; ey = j;
            }
        }
    }

    int dx[] = {1, -1, 0 , 0};
    int dy[] = {0,  0, 1 ,-1};
    char dirChar[] = { 'D' , 'U' , 'R', 'L'};

    vector<vector<char>> parent(n, vector<char>(m, 0));
    queue<pair<int,int>> q;
    q.push({sx, sy});
    grid[sx][sy] = '#';
    bool found = false;

    while(!q.empty()) {
        auto [cx , cy] = q.front(); q.pop();
        if (cx == ex && cy == ey){
            found = true;
            break;
        }

        for (int i=0; i<4; i++) {
            int nx = cx + dx[i]; int ny = cy + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && (grid[nx][ny]=='.' || grid[nx][ny]=='B')) {
                grid[nx][ny] = '#';
                parent[nx][ny] = dirChar[i];
                q.push({nx, ny});
            }
        }
    }

    if (found) {
        string path = "";
        int currX = ex, currY = ey;
        while(currX != sx || currY != sy) {
            char p = parent[currX][currY];
            path += p;

            if(p == 'D') currX--;
            else if(p == 'U') currX++;
            else if(p == 'R') currY--;
            else currY++;
        }
        reverse(path.begin(), path.end());
        cout << "YES\n";
        cout << path.length() << '\n';
        cout << path << '\n';
    } else {
        cout << "NO\n";
    }
}
/*
// Following solution is inefficient due to string copy, for large grid it will take a lot of time
struct val {
    int x;
    int y;
    string path="";
};
int n, m;
int sx=-1, sy=-1;
int ex=-1, ey=-1;
int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i<n ; i++) {
        for (int j = 0; j<m; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 'A'){
                sx = i; sy = j;
            } else if(grid[i][j] == 'B') {
                ex = i; ey = j;
            }
        }
    }
    queue<val> q;
    val v{sx, sy, ""};
    q.push(v);
    bool found=false;
    string path = "";
    while(!q.empty()) {
        val nv = q.front(); q.pop();
        int cx = nv.x; int cy = nv.y;
        int nx, ny;

        // D
        nx = cx + 1; ny = cy + 0;
        if(nx == ex && ny == ey) {
            path = nv.path + "D";
            found = true;
            break;
        }
        if(nx < n && nx>=0 && ny < m && ny >= 0 && grid[nx][ny] == '.') {
            grid[nx][ny] = '$';
            path = nv.path + "D";
            val tempv{nx, ny, path};
            q.push(tempv);
        }

        // U
        nx = cx - 1; ny = cy + 0;
        if(nx == ex && ny == ey) {
            path = nv.path + "U";
            found = true;
            break;
        }
        if(nx < n && nx>=0 && ny < m && ny >= 0 && grid[nx][ny] == '.') {
            grid[nx][ny] = '$';
            path = nv.path + "U";
            val tempv{nx, ny, path};
            q.push(tempv);
        }

        // R
        nx = cx + 0; ny = cy + 1;
        if(nx == ex && ny == ey) {
            path = nv.path + "R";
            found = true;
            break;
        }
        if(nx < n && nx>=0 && ny < m && ny >= 0 && grid[nx][ny] == '.') {
            grid[nx][ny] = '$';
            path = nv.path + "R";
            val tempv{nx, ny, path};
            q.push(tempv);
        }

        // L
        nx = cx + 0; ny = cy - 1;
        if(nx == ex && ny == ey) {
            path = nv.path + "L";
            found = true;
            break;
        }
        if(nx < n && nx>=0 && ny < m && ny >= 0 && grid[nx][ny] == '.') {
            grid[nx][ny] = '$';
            path = nv.path + "L";
            val tempv{nx, ny, path};
            q.push(tempv);
        }
    }
    if(found){
        cout << "YES\n";
        cout << path.length() << '\n';
        cout << path << '\n';
    } else{
        cout << "NO\n";
    }
}
*/