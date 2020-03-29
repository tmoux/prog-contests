#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pp = pair<pair<int,int>,int>;

const int maxn = 3e5+5, maxk = 19, M = 998244353;
int n, q;
vector<pair<int,int>> adj[maxn]; //to, wt
int depth[maxn];
int par[maxk][maxn];
int mx[maxk][maxn];
int tin[maxn], tout[maxn], t = 1;
void dfs(int i, int p, int l) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    mx[0][i] = l;
    for (int k = 1; k < maxk; k++) {
        mx[k][i] = max(mx[k-1][i],mx[k-1][par[k-1][i]]);
    }
    for (auto j: adj[i]) {
        if (j.first == p) continue;
        dfs(j.first,i,j.second);
    }
    tout[i] = t-1;
}
int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

int mx_walk(int lc, int u) {
    int res = 0;
    for (int k = maxk-1; k >= 0; k--) {
        if (depth[par[k][u]] >= depth[lc]) {
            res = max(res,mx[k][u]);
            u = par[k][u];
        }
    }
    return res;
}

int mx_dist(int u, int v) {
    int lc = lca(u,v);
    return max(mx_walk(lc,u),mx_walk(lc,v));
}

int radius[maxn]; //radius must be < radius[i]

int parent[maxn]; //memset to -1
int lone[maxn]; //0 = empty, > 0 = one, -1 = > 1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}
void Union(int x, int y, int r) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    if (lone[x] > 0) radius[lone[x]] = r;
    if (lone[y] > 0) radius[lone[y]] = r;

    parent[x] += parent[y];
    parent[y] = x;
    if (lone[y] > 0) {
        if (lone[x] > 0) {
            lone[x] = -1;
        }
        else if (lone[x] == 0) {
            lone[x] = lone[y];
        }
    }
    else if (lone[y] == -1) {
        lone[x] = -1;
    }
}

int solve(vector<int> special) {
    vector<int> sp = special;
    sort(sp.begin(),sp.end(),[](int a, int b) {
        return tin[a] < tin[b];
    });
    int nn = sp.size();
    for (int i = 1; i < nn; i++) {
        sp.push_back(lca(sp[i-1],sp[i]));
    }
    sort(sp.begin(),sp.end(),[](int a, int b) {
        return tin[a] < tin[b];
    });
    sp.erase(unique(sp.begin(),sp.end()),sp.end());
    //build compressed graph
    stack<int> st;
    vector<pair<pair<int,int>,int>> edges;
    for (auto i: sp) {
        radius[i] = 0;
        parent[i] = -1;
        lone[i] = 0;
        while (!st.empty() && tin[i] > tout[st.top()]) {
            st.pop();
        }
        if (!st.empty()) {
            int len = mx_walk(st.top(),i);
            edges.push_back({{st.top(),i},len});
            //cout << st.top() << ' ' << i << ' ' << len << endl;
        }
        st.push(i);
    }
    for (auto i: special) {
        lone[i] = i;
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
        return a.second < b.second;
            });
    for (auto& e: edges) {
        int u = e.first.first;
        int v = e.first.second;
        int len = e.second;
        Union(u,v,len);
    }
    /*
    for (auto i: special) {
        radius[i] = n;
    }
    for (auto i: special) {
        for (auto j: special) {
            if (i == j) continue;
            radius[i] = min(radius[i],mx_dist(i,j));
        }
    }
    */
    ll res = 1;
    for (auto i: special) {
        res = (res*radius[i]) % M;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back({b,i});
        adj[b].push_back({a,i});
    }
    dfs(1,0,0);
    cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<int> v;
        while (k--) {
            int ai; cin >> ai;
            v.push_back(ai);
        }
        if (v.size() == 1) {
            cout << n << '\n';
        }
        else cout << solve(v) << '\n';
    }
}
