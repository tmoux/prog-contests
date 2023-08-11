#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 123457;
set<int> adj[maxn];
int n, m;
bool special[maxn];
int inn[maxn];
bool bad[maxn];

int T = maxn + 5, maxDist = 0;

void DFS(int i, int p, int d) {
    //cout << i << ": " << d << '\n';
    if (d > maxDist) {
        maxDist = d;
        T = i;
    }
    else if (d == maxDist) {
        T = min(T,i);
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        if (bad[j]) continue;
        DFS(j,i,d+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        ++inn[u];
        ++inn[v];
    }
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        special[ai] = true;
        if (m == 1) {
            cout << ai << '\n';
            cout << 0 << '\n';
            return 0;
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) if (inn[i] == 1 && !special[i]) q.push(i);
    int numEdges = n-1;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        bad[f] = true;
        numEdges--;
        for (int i: adj[f]) {
            if (!special[i] && --inn[i] == 1) {
                q.push(i);
            }
        }
    }
    //cout << numEdges << '\n';
    for (int i = 1; i <= n; i++) {
        if (!bad[i]) {
            DFS(i,i,0);
            int en1 = T;
            T = maxn + 5;
            /*
            cout << "endpoint 1 : " << en1 << '\n';
            cout << "maxdist : " << maxDist << '\n';
            return 0;
            */
            DFS(en1,en1,0);
            int ans = 2*numEdges - maxDist;
            int st = min(en1,T);
            cout << st << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
}

