#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
int deg[maxn];
vector<int> adj[maxn];
bool vis[maxn];

set<pair<int,int>> v;

void remove(int i) {
    v.erase({deg[i],i});
    vis[i] = true;
    for (auto j: adj[i]) {
        if (vis[j]) continue;
        v.erase({deg[j],j});
        --deg[j];
        v.insert({deg[j],j});
    }
}

bool onpath[maxn];
int dist[maxn];
int par[maxn];
void dfs(int i, int p, int d) {
    dist[i] = d;
    par[i] = p;
    onpath[i] = true;
    for (int j: adj[i]) {
        if (vis[j] || onpath[j]) continue;
        dfs(j,i,d+1);
        return;
    }
    pair<int,int> mn = {maxn,-1};
    for (int j: adj[i]) {
        if (vis[j]) continue;
        mn = min(mn,{dist[j],j});
    }
    vector<int> cyc;
    int curr = i;
    while (true) {
        cyc.push_back(curr);
        if (curr == mn.second) break;
        curr = par[curr];
    }
    cout << 2 << '\n';
    cout << cyc.size() << '\n';
    for (auto j: cyc) {
        cout << j << ' ';
    }
    cout << '\n';
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ++deg[a]; ++deg[b];
    }
    int target = 1;
    while (target*target < n) target++;
    for (int i = 1; i <= n; i++) {
        v.insert({deg[i],i});
    }
    vector<int> ind_set;
    while (ind_set.size() < target) {
        auto p = *v.begin();
        //cout << p.first << ' ' << p.second << endl;
        if (vis[p.second]) continue;
        if (p.first >= target-1) {
            //find cycle
            dfs(p.second,p.second,0);
        }
        else {
            ind_set.push_back(p.second);
            remove(p.second);
            for (auto j: adj[p.second]) {
                if (vis[j]) continue;
                remove(j);
            }
        }
    }
    cout << 1 << '\n';
    for (auto j: ind_set) {
        cout << j << ' ';
    }
    cout << '\n';
}
