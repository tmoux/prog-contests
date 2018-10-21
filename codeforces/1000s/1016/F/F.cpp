#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int N, M, nodes[maxn];
ll d1[maxn], dn[maxn];
struct Edge { int v, w; };
vector<Edge> adj[maxn];

void dfs1(int i, int par, ll* d) {
    for (Edge& e: adj[i]) {
        if (e.v == par) continue;
        d[e.v] = d[i] + e.w;
        dfs1(e.v,i,d);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,1,d1);
    dfs1(N,N,dn);
    for (int i = 1; i <= N; i++) nodes[i-1] = i;
    sort(nodes,nodes+N,
        [](int& a, int& b) { return d1[a]-dn[a] > d1[b]-dn[b];});


    auto cmp = [](int a, int b) { return dn[a] > dn[b]; }; //max is s.begin()
    set<int, decltype(cmp)> s(cmp);
    ll maxd = 0;
    for (int a = 0; a < N; a++) {
        int i = nodes[a];
        vector<int> adds;
        for (Edge e: adj[i]) {
            if (s.erase(e.v)) adds.push_back(e.v);
        }
        if (!s.empty()) maxd = max(maxd,d1[i] + dn[*s.begin()]);
        //cout << i << ' ' << *s.begin() << ' ' << (d1[i] + dn[*s.begin()]) << '\n';
        s.insert(i);
        for (int j: adds) s.insert(j);
    }

    //cout << maxd << '\n';
    while (M--) {
        int xj; cin >> xj;
        cout << min(d1[N],maxd+xj) << '\n';
    }


    return 0;
}
	

