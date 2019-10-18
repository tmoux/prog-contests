#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int q, n;
vector<int> adj[maxn];

pair<int,int> dfs(int i, int p) {
    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> q;
    while (q--) {
        cin >> n;
        //reset
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < n-1; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (n <= 2) {
            cout << n << '\n';
        }
        else {
            for (int i = 1; i <= n; i++) {
                if (adj[i].size() > 1) {
                    auto ans = dfs(i,i);
                    cout << ans.second << '\n';
                    break;
                }
            }
        }
    }
}
