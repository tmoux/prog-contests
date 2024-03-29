#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];

int mxd = -1, d = -1;
void dfs(int i, int p, int dist) {
    if (dist > mxd) {
        mxd = dist;
        d = i;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,dist+1);
    }
}

int par[maxn];
int depth[maxn], maxd[maxn];
void root(int i, int p) {
    par[i] = p;
    depth[i] = depth[p] + 1;
    maxd[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i);
        maxd[i] = max(maxd[i],maxd[j]+1);
    }
}

int mx = 0, subtree = -1;

int a, b, c;
int cmax = -1;

void solve(int i, int child) {
    for (int j: adj[i]) {
        if (j == child || j == par[i]) continue;
        int tr = maxd[j];
        //cout << i << ": " << tr << endl;
        if (tr > mx) {
            mx = tr;
            subtree = j;
        }
    }
    if (i != a) solve(par[i],i);
}

void getDeepest(int i) {
    if (depth[i] > cmax) {
        c = i;
        cmax = depth[i];
    }
    for (int j: adj[i]) {
        if (j == par[i]) continue;
        getDeepest(j);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> leafs;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            leafs.push_back(i);
        }
    }
    if (leafs.size() == 2) {
        cout << n-1 << '\n';
        cout << leafs[0] << ' ' << leafs[1] << ' ';
        for (int i = 1; i <= n; i++) {
            if (i != leafs[0] && i != leafs[1]) {
                cout << i << '\n';
                break;
            }
        }
        return 0;
    }
    dfs(1,1,0);
    a = d;
    mxd = d = -1;
    dfs(a,a,0);
    b = d;
    root(a,a);
    solve(b,b);
    int ans = depth[b]-depth[a]+mx;
    getDeepest(subtree);
    cout << ans << '\n';
    cout << a << ' ' << b << ' ' << c << '\n';
}
