#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
struct DSU
{
    vector<int> p, d;
    DSU(int n) {
        p = vector<int>(n+1,-1);
        d = vector<int>(n+1,0);        
    }
    int Find(int x) {
        return p[x] < 0 ? x : p[x] = Find(p[x]);
    }
    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (rand() % 2) swap(x,y);
        p[x] += p[y];
        d[x] += d[y];    
        p[y] = x;
    }
};

struct Edge
{
    int to, w;
};

vector<Edge> adj[maxn];

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back({v,c});
        adj[v].push_back({u,c});
    }
    vector<DSU> dsu = {DSU(n),DSU(n)};

    for (int i = 1; i <= n; i++) {
        for (Edge e: adj[i]) {
            int f = e.w == 0 ? 1 : 0;
            dsu[f].d[i]++;
        }
        for (Edge e: adj[i]) {
            dsu[e.w].Union(i,e.to);
        }
    }

    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d: %d\n",i,dsu[j].Find(i));
            printf("size = %d, d = %d\n",-dsu[j].p[dsu[j].Find(i)],dsu[j].d[dsu[j].Find(i)]);
        }
    }
    */
    ll ans = 0;
    set<int> f[2];
    for (int i = 1; i <= n; i++) {
        int j = dsu[0].Find(i);
        if (!f[0].count(j)) {
            f[0].insert(j);
            ans += -dsu[0].p[j] + dsu[0].d[j] - 1;
        }

        j = dsu[1].Find(i);
        if (!f[1].count(j)) {
            f[1].insert(j);
            ans += -dsu[1].p[j] + dsu[1].d[j] - 1;
        }
    }
    cout << ans << '\n';


    return 0;
}

