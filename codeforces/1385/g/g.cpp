#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int a[2][maxn];

vector<int> rs[2][maxn];
set<int> adj[2*maxn];

int conv(int i, int j) {
    return i*n + j;
}

void add_edge(int i, int j) {
    adj[i].insert(j);
    adj[j].insert(i);
}

void solve() {
    cin >> n;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            rs[i][j].clear();
        }
    }
    for (int i = 0; i <= 2*n; i++) {
        adj[i].clear();
    }
    map<int,int> mp;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            rs[i][a[i][j]].push_back(j);
            ++mp[a[i][j]];
        }
    }
    bool poss = true;
    for (int i = 1; i <= n; i++) {
        if (mp[i] != 2) {
            poss = false;
        }
    }
    if (!poss) {
        cout << "-1" << '\n';
        return;
    }
    for (int j = 0; j < n; j++) {
        for (int k: rs[0][a[0][j]]) {
            if (k == j) continue;
            add_edge(conv(0,j),conv(0,k));
        }
        for (int k: rs[1][a[1][j]]) {
            if (k == j) continue;
            add_edge(conv(0,j),conv(0,k));
        }

        for (int k: rs[1][a[0][j]]) {
            if (k == j) continue;
            add_edge(conv(1,j),conv(0,k));
        }
        for (int k: rs[0][a[1][j]]) {
            if (k == j) continue;
            add_edge(conv(1,j),conv(0,k));
        }

        add_edge(conv(0,j),conv(1,j));
    }
    vector<int> color(2*n,-1);
    int ans = 0;
    vector<int> ret;
    for (int i = 0; i < 2*n; i++) {
        if (color[i] != -1) continue;
        vector<vector<int>> v(2);
        queue<int> q;
        q.push(i);
        color[i] = 0;
        while (!q.empty()) {
            int f = q.front(); q.pop();
            v[color[f]].push_back(f);
            for (int j: adj[f]) {
                if (color[j] == -1) {
                    color[j] = 1^color[f];
                    q.push(j);
                }
                else if (color[j] == (1^color[f])) {
                    //do nothing
                }
                else if (color[j] == color[f]) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
        int c0 = 0;
        for (int i: v[0]) if (i >= n) c0++;
        int c1 = 0;
        for (int i: v[1]) if (i >= n) c1++;
        if (c0 < c1) {
            ans += c0;
            for (int i: v[0]) if (i >= n) ret.push_back(i);
        }
        else {
            ans += c1;
            for (int i: v[1]) if (i >= n) ret.push_back(i);
        }
        /*
        cout << i << ": ";
        for (int j: adj[i]) {
            cout << j << ' ';
        }
        cout << '\n';
        */
    }
    cout << ans << '\n';
    for (int i: ret) {
        cout << (i%n)+1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
