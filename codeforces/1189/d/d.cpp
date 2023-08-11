#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int deg[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    bool poss = true;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 2) {
            poss = false;
            break;
        }
    }
    cout << (poss ? "YES" : "NO") << '\n';
}

