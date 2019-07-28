#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
int a[maxn];

int odds[maxn], evens[maxn];
void add(int bit[], int i, int x) {
    for (; i <= n+1; i += i & (-i))
        bit[i] += x;
}

int sum(int bit[], int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

vector<int> adj[maxn];
int tin[maxn], tout[maxn];
int pt = 1;
int depth[maxn];
void DFS(int i, int p) {
    depth[i] = depth[p] + 1;
    tin[i] = pt++;
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS(j,i);
    }
    tout[i] = pt-1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1,1);
    for (int i = 1; i <= n; i++) {
        if (depth[i] % 2 == 0) {
            add(evens,tin[i],a[i]);
            add(evens,tin[i]+1,-a[i]);
        }
        else {
            add(odds,tin[i],a[i]);
            add(odds,tin[i]+1,-a[i]);
        }
    }
    while (m--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            int val; cin >> val;
            int *a = evens, *b = odds;
            if (depth[x] % 2 == 1) swap(a,b);
            add(a,tin[x],val);
            add(a,tout[x]+1,-val);
            add(b,tin[x],-val);
            add(b,tout[x]+1,val);
        }
        else {
            int res = (depth[x] % 2 == 0 ? sum(evens,tin[x]) : sum(odds,tin[x]));
            cout << res << '\n';
        }
    }
}

