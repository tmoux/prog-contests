#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int maxn = 1e6+6;
int n, m;
vector<int> adj[maxn];
bool seen[maxn];
ll degree[maxn];

inline ll ch2(ll x) {
    return x*(x-1)/2;
}

gp_hash_table<int,int> edges;
int cnt = 0;
void dfs(int i) {
    seen[i] = true;
    for (int j: adj[i]) {
        auto p = make_pair(min(i,j),max(i,j));
        if (edges[p.first].count(p.second)) {
            continue;
        }
        else {
            edges.insert(p);
            cnt++;
            if (!seen[j]) dfs(j);
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d %d",&n,&m);
    int loops = 0;
    int start;
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d",&u,&v);
        start = u;
        if (u == v) loops++;
        else {
            degree[u]++;
            degree[v]++;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(start);
    if (cnt < m) {
        cout << 0 << '\n';
        return 0;
    }
    ll ans = 1LL*loops*(m-1)-ch2(loops);
    for (int i = 1; i <= n; i++) {
        ans += ch2(degree[i]);
    }
    cout << ans << '\n';

    return 0;
}

