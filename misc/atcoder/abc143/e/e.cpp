#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305, INF = 1e9+9;
int n, m, l;

int adj[maxn][maxn];
int ng[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = INF;
            ng[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; i++) {
        adj[i][i] = 0;
        ng[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a][b] = c;
        adj[b][a] = c;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (adj[i][j] > adj[i][k] + adj[k][j]) 
                    adj[i][j] = adj[i][k] + adj[k][j];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (adj[i][j] <= l) {
                ng[i][j] = 1;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (ng[i][j] > ng[i][k] + ng[k][j]) 
                    ng[i][j] = ng[i][k] + ng[k][j];
            }
        }
    }
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        cout << (ng[a][b] >= INF ? -1 : ng[a][b]-1) << '\n';
    }
}
