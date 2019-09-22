#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
int w[maxn];
vector<int> adj[maxn];
int deg[maxn];

bool vis[maxn];

int child[maxn];
ll csum[maxn];
int s;
bool unuse[maxn];

void dfs(int i) {
    vis[i] = true;
    for (int j: adj[i]) {
        if (vis[j]) continue;
        dfs(j);
        //cout << j << ": " << deg[j] << '\n';
        if (deg[j] <= 2 && csum[child[j]] != -1) {
            unuse[j] = 1;
            csum[child[j]] += w[j];
            child[i] = child[j];
        }
    }
    if (deg[i] == 1 && i != s) {
        child[i] = i;
        csum[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(csum,-1,sizeof csum);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++deg[u];
        ++deg[v];
    }
    cin >> s;
    dfs(s);
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << csum[i] << '\n';
        cout << child[i] << '\n';
    }
    */
    ll ans = 0;
    ll maxLeaf = 0;
    for (int i = 1; i <= n; i++) {
        if (!unuse[i]) ans += w[i];
        if (csum[i] != -1) maxLeaf = max(maxLeaf,csum[i]);
    }
    cout << (ans + maxLeaf) << '\n';
}
