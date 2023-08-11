#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+3;
int n;
pair<int,int> grid[maxn][maxn];
char ans[maxn][maxn];

map<pair<int,int>,vector<pair<int,int>>> mp;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
char cv[] = {'L','U','R','D'};
char rev[] = {'R','D','L','U'};

bool valid(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < n;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = '#';
            int a, b; cin >> a >> b;
            --a; --b;
            grid[i][j] = {a,b};
            if (a != -2) {
                mp[make_pair(a,b)].push_back({i,j});
            }
        }
    }
    for (auto p: mp) {
        int x = p.first.first;
        int y = p.first.second;
        if (grid[x][y] != make_pair(x,y)) {
            cout << "INVALID\n";
            return 0;
        }
        queue<pair<int,int>> q;
        q.push({x,y});
        ans[x][y] = 'X';
        int cnt = 0;
        while (!q.empty()) {
            cnt++;
            auto f = q.front(); q.pop();
            for (int k = 0; k < 4; k++) {
                int nx = f.first + dx[k];
                int ny = f.second + dy[k];
                if (!valid(nx,ny)) continue;
                if (grid[nx][ny] != make_pair(x,y)) continue;
                if (ans[nx][ny] == '#') {
                    ans[nx][ny] = cv[k];
                    q.push({nx,ny});
                }
            }
        }
        if (cnt != p.second.size()) {
            cout << "INVALID\n";
            return 0;
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j] == '#') {
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (!valid(ni,nj)) continue;
                    if (grid[ni][nj].first == -2) {
                        ans[i][j] = rev[k];
                        break;
                    }
                }
            }
        }
    }
    //check if good
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j] == '#') {
                cout << "INVALID\n";
                return 0;
            }
        }
    }
    cout << "VALID\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}
