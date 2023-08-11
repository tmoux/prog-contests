#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, INF = 2e9;
int N, M, dist[maxn];
vector<int> adj[maxn], reds;
pair<int,int> queries[maxn];
int parent[maxn][18], depth[maxn];

void dfs(int i, int par) {
    parent[i][0] = par;
    for (int j: adj[i]) {
        if (j == par) continue;
        depth[j] = depth[i] + 1;
        dfs(j,i);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u,v);
    for (int k = 17; k >= 0; k--) {
        int poss = parent[v][k];
        if (poss != -1 && depth[poss] >= depth[u]) {
            v = poss;
        }
    }
    assert(depth[u] == depth[v]);
    if (u == v) return u;
    for (int k = 17; k >= 0; k--) {
        int uu = parent[u][k];
        int vv = parent[v][k];
        if (uu != vv) {
            u = uu;
            v = vv;
        }
    }
    assert(parent[u][0] != -1);
    return parent[u][0];
}

ll pd(int u, int v) {
    return (ll)depth[u] + depth[v] - 2 * depth[lca(u,v)];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < M; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    //precomp lca
    depth[1] = 0;
    dfs(1,-1);
    for (int k = 1; k < 17; k++) {
        for (int i = 1; i <= N; i++) {
            if (parent[i][k-1] == -1) parent[i][k] = -1;
            else parent[i][k] = parent[parent[i][k-1]][k-1];
        }
    }
    //calc
    reds.push_back(1);
    int block = (int)(sqrt(M))+1;
    int idx = 0;
    while (idx < M) {
        for (int i = 1; i <= N; i++) dist[i] = INF;
        queue<int> q;
        for (int i: reds) {
            dist[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int f = q.front();
            for (int j: adj[f]) {
                if (dist[f] + 1 < dist[j]) {
                    dist[j] = dist[f] + 1;
                    q.push(j);
                }
            }
            q.pop();
        }

        vector<int> adds;
        for (int i = idx; i < idx + block; i++) {
            if (i >= M) break;
            if (queries[i].first == 1) {
                adds.push_back(queries[i].second);
            }
            else {
                int v = queries[i].second;
                ll ans = dist[v];
                for (int nx: adds) {
                    ans = min(ans,pd(v,nx));
                }
                cout << ans << '\n';
            }
        }
        for (int i: adds) reds.push_back(i);
        idx += block;
    }

    return 0;
}
	

