#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, k;
vector<int> adj[maxn];
bool blocked[maxn];
int degree[maxn], removed[maxn];

bool dfs(int i, int p, int k) {
    int cnt = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        cnt++;
        if (!dfs(j,i,k-1)) return false;
    }
    if (cnt == 0) return k == 0;
    if (k == 0) return cnt == 0;
    return cnt >= 3;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++; degree[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) q.push(i);        
    }
    int center = 1;
    while (!q.empty()) {
        int f = q.front();
        blocked[f] = true;
        center = f;
        for (int j: adj[f]) {
            if (blocked[j]) continue;
            blocked[j] = true;
            q.push(j);
        }
        q.pop();
    }
    //now found center
    bool is = dfs(center,center,k);
    cout << (is ? "Yes" : "No") << '\n';

    return 0;
}

