#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n, q;
vector<int> adj[maxn];
struct Query {
    int d, x;    
};

vector<Query> queries[maxn];

int depth[maxn];
void root(int i, int p, int d) {
    depth[i] = d;
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i,d+1);
    }
}

ll ans[maxn], accum[maxn];
void add(int i, int x, ll* bit) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

void addRange(int l, int r, int x, ll* bit) {
    add(l,x,bit);
    add(r+1,-x,bit);
}

ll sum(int i, ll* bit) {
    ll r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

void dfs(int i, int p) {
    for (Query q: queries[i]) 
        addRange(depth[i],depth[i]+q.d,q.x,accum);
    /*
    cout << i << ":\n";
    for (int j = 1; j <= 3; j++) {
        cout << sum(j,ans) << ' ';
    }
    cout << '\n';
    printf("Node %d: depth = %d, ans=%d\n",i,depth[i],sum(depth[i],ans));
    */
    ans[i] = sum(depth[i],accum);
    //cout << i << ": " << ans[i] << '\n';
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    for (Query q: queries[i]) 
        addRange(depth[i],depth[i]+q.d,-q.x,accum);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(1,1,1);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int v, d, x; cin >> v >> d >> x;
        d = min(d,n-depth[v]);
        queries[v].push_back({d,x});
    }
    dfs(1,1);
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n "[i==n];
    }

    return 0;
}

