#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
vector<int> adj[maxn];

vector<int> s, f;
bool seen[maxn];

void DFS(int i, int d) {
    seen[i] = true;
    if (d == 0) s.push_back(i);
    else f.push_back(i);
    for (int j: adj[i]) {
        if (seen[j]) continue;
        DFS(j,d^1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        s.clear();
        f.clear();
        for (int i = 1; i <= n; i++) {
            seen[i] = false;
        }
        DFS(1,0);
        if (s.size() <= n/2) {
            cout << s.size() << '\n';
            for (int i: s) {
                cout << i << ' ';
            }
            cout << '\n';
        }
        else if (f.size() <= n/2) {
            cout << f.size() << '\n';
            for (int i: f) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    }
}

