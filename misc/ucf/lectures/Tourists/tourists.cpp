#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1000;
const int maxk = 11;
int depth[maxn], par[maxk][maxn], n;
bool seen[maxn];
vector<int> adj[maxn];

void dfs(int i, int paren) {
    par[0][i] = paren;
    for (int j: adj[i]) {
        if (j != paren) {
            depth[j] = depth[i] + 1;
            dfs(j,i);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    //int diff = depth[b] - depth[a];
    for (int k = maxk - 1; k >= 0; k--) {
        int to = par[k][b];
        if (to != -1 && depth[to] >= depth[a]) {
            b = to;
        }
    }
    //now depth[a] == depth[b]
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int newA = par[k][a];
        int newB = par[k][b];
        if (newA != newB) {
            a = newA;
            b = newB;
        }
    }
    return par[0][a];
}

ll dist(int a, int b) {
    return (ll)depth[a] + depth[b] - 2 * depth[lca(a,b)];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        memset(par,-1,sizeof(par));
        for (int i = 1; i <= n; i++) {
            int m; cin >> m;
            while (m--) {
                int ai; cin >> ai;
                adj[i].push_back(ai);
                adj[ai].push_back(i);
            }
        }
        
        par[0][1] = -1;
        dfs(1,-1);
        for (int k = 1; k < maxk; k++) {
            for (int i = 1; i <= n; i++) {
                if (par[k-1][i] == -1) {
                    par[k][i] = -1;
                }
                else {
                    par[k][i] = par[k-1][par[k-1][i]];
                }
            }
        }
        int q; cin >> q;
        cout << "Case " << a << ":\n";
        while (q--) {
            int u, v; cin >> u >> v;
            cout << lca(u,v) << '\n';
        }
    }
    return 0;
}
	

