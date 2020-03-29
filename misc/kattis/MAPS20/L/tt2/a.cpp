#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
vector<int> inn[maxn], out[maxn];
set<int> condense[maxn], rev[maxn];
bool visited[maxn];
int sz[maxn];
int comp[maxn];
deque<int> L;
void visit(int now) {
    if (!visited[now]) {
        visited[now] = true;
        for (int j: inn[now]) {
            visit(j);
        }
        L.push_front(now);
    }
}

void assign(int u, int root) {
    if (comp[u] == -1) {
        comp[u] = root;
        sz[root]++;
        for (int j: out[u]) {
            assign(j,root);
        }
    }
}

int deg[maxn];

set<int> par[maxn], child[maxn];

void merge(set<int>&a, set<int>& b) {
    for (auto i: a) {
        b.insert(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(comp,-1,sizeof comp);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        inn[u].push_back(v);
        out[v].push_back(u);
    }
    //Kosaraju
    for (int i = 0; i < n; i++) {
        visit(i);
    }
    for (int u: L) {
        assign(u,u);
    }
    //create condensation graph
    set<int> s;
    for (int i = 0; i < n; i++) {
        //cout << i << ": " << comp[i] << endl;
        s.insert(comp[i]);
        for (int j: inn[i]) {
            if (comp[i] == comp[j]) continue;
            condense[comp[i]].insert(comp[j]);
            rev[comp[j]].insert(comp[i]);
        }
    }
    queue<int> q;
    for (int i: s) {
        if (sz[i] > 1) continue;
        deg[i] = rev[i].size();
        if (deg[i] == 0) q.push(i);
    }
    vector<int> v;
    while (!q.empty()) {
        int i = q.front(); q.pop();
        v.push_back(i);
        for (int j: condense[i]) {
            if (sz[j] > 1) continue;
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    for (int i = 0; i < v.size(); i++) {
        par[v[i]].insert(v[i]);
        for (int j = i+1; j < v.size(); j++) {
            if (condense[v[i]].count(v[j])) merge(par[v[i]],par[v[j]]);
        }
    }
    for (int i: v) {
        for (int j: par[i]) {
            child[j].insert(i);
        }
    }
    random_device device;
    mt19937 gen(device());
    int ans = 0;
    for (int _ = 0; _ < 10000; _++) {
        shuffle(v.begin(),v.end(),gen);
        vector<bool> vis(n);
        int cnt = 0;
        for (int i: v) {
            if (!vis[i]) {
                vis[i] = true;
                ++cnt;
                for (int j: par[i]) vis[j] = true;
                for (int j: child[i]) vis[j] = true;
            }
        }
        ans = max(ans,cnt);
    }
    cout << ans << '\n';
}
