#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

map<char,int> dx = {
    {'L',0},
    {'R',0},
    {'U',-1},
    {'D',1}
};

map<char,int> dy = {
    {'L',-1},
    {'R',1},
    {'U',0},
    {'D',0}
};

int dxx[] = {0,1,0,-1};
int dyy[] = {1,0,-1,0};

vector<vector<char>> grid;
vector<vector<int>> color;
vector<vector<bool>> vis;
vector<vector<int>> mp;

int n, m;

bool valid(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
};

pair<int,int> get_next(int i, int j, char c) {
    return make_pair(i+dx[c],j+dy[c]);
};

map<pi,vector<pi>> adj, rev;

void get_graph(int i, int j) {
    queue<pi> q;
    vis[i][j] = true;
    q.push({i,j});
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int i = p.first, j = p.second;
        //cout << i << ' ' << j << endl;
        auto nxt = get_next(i,j,grid[i][j]);
        if (valid(nxt.first,nxt.second)) {
            adj[make_pair(i,j)].push_back(nxt);
            if (!vis[nxt.first][nxt.second]) {
                vis[nxt.first][nxt.second] = true;
                q.push({nxt.first,nxt.second});
            }
        }
        for (int k = 0; k < 4; k++) {
            int ni = i + dxx[k];
            int nj = j + dyy[k];
            if (!valid(ni,nj)) continue;
            if (get_next(ni,nj,grid[ni][nj]) == make_pair(i,j)) {
                rev[make_pair(i,j)].push_back(make_pair(ni,nj));
                if (!vis[ni][nj]) {
                    vis[ni][nj]= true;
                    q.push({ni,nj});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        grid = vector<vector<char>>(n,vector<char>(m));
        color = vector<vector<int>>(n,vector<int>(m));
        vis = vector<vector<bool>>(n,vector<bool>(m,false));
        mp = vector<vector<int>>(n,vector<int>(m,-1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c; cin >> c;
                color[i][j] = c-'0';
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        auto solve = [&](int i, int j) {
            set<pi> seen;
            pi cur = {i,j};
            vector<pi> st;
            vector<pi> cyc;
            while (true) {
                seen.insert(cur);
                st.push_back(cur);
                pi nxt = adj[cur][0];
                if (seen.count(nxt)) {
                    while (true) {
                        cyc.push_back(st.back());
                        st.pop_back();
                        if (cyc.back() == nxt) {
                            break;
                        }
                    }
                    break;
                }
                else cur = nxt;
            }
            int len = cyc.size();
            //cout << "len = " << len << endl;
            vector<bool> equiv(len);
            queue<pi> q;
            for (int i = 0; i < len; i++) {
                mp[cyc[i].first][cyc[i].second] = i;
                q.push(cyc[i]);
            }
            while (!q.empty()) {
                auto p = q.front(); q.pop();
                if (color[p.first][p.second] == 0) {
                    equiv[mp[p.first][p.second]] = true;
                }
                for (auto r: rev[p]) if (mp[r.first][r.second] == -1) {
                    mp[r.first][r.second] = (mp[p.first][p.second]+1+len) % len;
                    q.push(r);    
                }
            }
            int cnt = accumulate(equiv.begin(),equiv.end(),0);
            return make_pair(len,cnt);
        };

        int total = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j]) continue;
                adj.clear();
                rev.clear();
                get_graph(i,j);
                auto p = solve(i,j);
                total += p.first;
                ans += p.second;
            }
        }
        cout << total << ' ' << ans << '\n';
    }
}
