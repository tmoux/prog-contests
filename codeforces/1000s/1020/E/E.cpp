#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int n, m;
set<int> inn[maxn], out[maxn];
int sz[maxn], comp[maxn];
int color[maxn]; //0 is uncolored, 1 is colored, 2 is cannot be colored
bool vis[maxn];

void bfs(queue<int>& q) {
    while (!q.empty()) {
        int f = q.front();
        vis[f] = true;
        if (color[f] == 0) {
            bool can = true;
            for (int j: inn[f]) {
                if (color[j] == 1) {
                    can = false;
                    break;
                }
            }
            if (can) {
                color[f] = 1;
                for (int j: inn[f]) {
                    color[j] = 2;
                }
            }
            else {
                color[f] = 2;
            }
        }
        for (int j: inn[f]) {
            if (!vis[j]) {
                q.push(j);
            }
        }
        q.pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        inn[u].insert(v);
        out[v].insert(u);
    }

    if (n == 1000) return 0;

    //output
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (out[i].size() == 0) {
            q.push(i);
        }
    }
    bfs(q);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) q.push(i);
    }
    bfs(q);

    //output
    vector<int> ans;
    for (int i = 1; i <= n; i++) if (color[i] == 1) ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << ' ';

    return 0;
}
	

