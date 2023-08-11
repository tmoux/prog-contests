#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int deg[maxn];
int ans[maxn];
struct Edge
{
    int from, to, id;
};
vector<Edge> edges;

int farthest = -1;
int dist = -1;
int par[maxn];
void dfs(int i, int p, int d) {
    par[i] = p;
    if (d > dist) {
        dist = d;
        farthest = i;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,d+1);
    }
}
map<pair<int,int>,int> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ++deg[a];
        ++deg[b];
        edges.push_back({a,b,i});
        mp[make_pair(a,b)] = i;
        mp[make_pair(b,a)] = i;
    }
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx,deg[i]);
    }
    if (mx == n-1) {
        //star
        for (int i = 0; i < n-1; i++) {
            cout << i << '\n';
        }
        return 0;
    }

    memset(ans,-1,sizeof ans);
    dfs(1,1,0);
    int root = farthest;
    farthest = -1;
    dist = -1;
    dfs(root,root,0);
    int i = farthest;
    ans[mp[make_pair(i,par[i])]] = 1;
    i = par[i];
    int pt = n-2;
    while (true) {
        if (par[i] == root) {
            ans[mp[make_pair(i,par[i])]] = 0;
            break;
        }
        else {
            ans[mp[make_pair(i,par[i])]] = pt--;
            i = par[i];
        }
    }
    for (int i = 0; i < edges.size(); i++) {
        if (ans[i] == -1) {
            ans[i] = pt--;
        }
    }
    for (int i = 0; i < edges.size(); i++) {
        cout << ans[i] << '\n';
    }
}
