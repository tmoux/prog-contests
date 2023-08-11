#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
vector<int> adj[maxn];
int par[maxn];
int tin[maxn], tout[maxn], t = 0;
int depth[maxn];

void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    tin[i] = t++;
    par[i] = p;
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
    }
    tout[i] = t-1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,1);
    while (m--) {
        int k; cin >> k;
        set<int> s;
        while (k--) {
            int ai; cin >> ai;
            s.insert(par[ai]);
        }
        bool poss = true;
        vector<int> v;
        for (auto i: s) {
            v.push_back(i);
        }
        sort(v.begin(),v.end(),[](auto a, auto b) {
                return depth[a] < depth[b];
                });
        for (int i = 1; i < v.size(); i++) {
            if (tin[v[i-1]] <= tin[v[i]] && tin[v[i]] <= tout[v[i-1]]) {

            }
            else {
                poss = false;
                break;
            }
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }
}
