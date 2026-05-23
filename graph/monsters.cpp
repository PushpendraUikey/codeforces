#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1194
// The question tests the reachability of monster to the person, time based

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return false;

    vector<string> grid(n);
    queue<pair<int,int>> mq;
    queue<pair<int,int>> pq;
    vector<vector<int>> m_time(n, (vector<int>(m, INT_MAX)));
    vector<vector<int>> p_time(n, (vector<int>(m, INT_MAX)));
    vector<vector<char>> parent(n, vector<char>(m, 0));

    int sx = -1, sy = -1;

    for(int i=0; i<n; i++) {
        cin >> grid[i];
        for(int j = 0; j<m ;  j++) {
            if(grid[i][j] == 'M') {
                mq.push({i,j});
                m_time[i][j] = 0;
            } else if (grid[i][j] == 'A') {
                sx = i; sy = j;
                pq.push({i, j});
                p_time[i][j] = 0;
            }
        }
    }


    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    char dir[4] = {'D', 'U', 'R', 'L'};

    // multi source bfs for monsters 
    while(!mq.empty()) {
        auto [x, y] = mq.front(); mq.pop();
        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx>=0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#') {
                if(m_time[nx][ny] > m_time[x][y] + 1) {
                    m_time[nx][ny] = m_time[x][y] + 1;
                    mq.push({nx, ny});
                }
            }
        }
    }

    int ex = -1, ey = -1;
    // Trying to escape the player out of maze
    while(!pq.empty()) {
        auto [x, y] = pq.front(); pq.pop();

        if(x == 0 || x == n-1 || y == 0 || y == m-1) {
            ex = x;
            ey = y;
            break;
        }

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#') {
                if(p_time[x][y]+1 < m_time[nx][ny] && p_time[x][y]+1 < p_time[nx][ny]) {
                    p_time[nx][ny] = p_time[x][y] + 1;
                    pq.push({nx, ny});
                    parent[nx][ny] = dir[i];
                }
            }
        }
    }

    if(ex != -1) {
        cout << "YES\n";
        string path = "";
        int currX = ex; int currY = ey;
        while(currX != sx || currY != sy) {
            char p = parent[currX][currY];
            path += p;
            if(p == 'D') currX--;
            else if(p == 'U') currX++;
            else if(p == 'R') currY--;
            else if(p == 'L') currY++;
        }

        reverse(path.begin(), path.end());
        cout << path.length() << '\n';
        cout << path << '\n';
    } else {
        cout << "NO\n";
    }
}

/*
Wrong approach

int n=-1, m=-1;
int sx=0,sy=0;
vector<string> grid;
set<pair<int,int>> monsterPos;
void increase_monsterRange() {
    cout << "Inside Monster Increase range\n";
    int rx[4] = {1, -1, 0, 0};
    int ry[4] = {0,  0, 1, -1};
    for (auto &p : monsterPos) {
        auto [x, y] = p;
        monsterPos.erase(p);
        for(int i=0; i<4; i++) {
            int nx = x + rx[i];
            int ny = y + ry[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.'){
                grid[nx][ny] = 'M';
                monsterPos.insert({nx, ny});
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>n>>m)) return 0;
    cout << "Grid size: " << n << ' ' << m << '\n';
    grid.resize(n);
    for (int i=0; i<n; i++) {
        cin >> grid[i];
        for (int j=0; j<m; j++) {
            if(grid[i][j] == 'A'){
                sx=i;
                sy=j;
            }
            else if(grid[i][j] == 'M') {
                monsterPos.insert({i,j});
            }
        }
    }

    int rx[4] = {1, -1, 0, 0};
    int ry[4] = {0,  0, 1, -1};
    char dir[4] = {'D', 'U', 'R', 'L'};

    vector<vector<char>> parent(n, vector<char>(m, 0));
    queue<pair<int,int>> q;
    q.push({sx, sy});

    while(!q.empty()) {
        auto [x, y] = q.front();   q.pop();
        if(monsterPos.count({x, y}) > 0) {
            continue;
        }
        increase_monsterRange();
        cout << "Current position: " << x << ' ' << y << '\n';  
        for (int i=0; i<4; i++) {
            int nx = rx[i] + x;
            int ny = ry[i] + y;

            if(nx>=0 && nx < n && ny>=0 && ny < m && grid[nx][ny] == '.'){
                if(nx == 0 || nx == n-1 || ny == 0 || ny == m-1){
                    cout << "Found exit at " << nx << ' ' << ny << '\n';
                    string path = "";
                    int currX = nx, currY = ny;
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
                    monsterPos.clear();

                    return 0;
                }
                grid[nx][ny] = '#';
                parent[nx][ny] = dir[i];
                q.push({nx, ny});
            }
        }
    }
    monsterPos.clear();
    cout << "NO\n";
}
    */