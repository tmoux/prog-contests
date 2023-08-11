#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
vector<int> adj[maxn];

int depth[maxn];
int wt[maxn];
ll ans = 0;

int par[maxn];
int deg[maxn];
int sub[maxn];

set<pair<int,int>> s;

void dfs(int i, int p, int d) {
    //cout << "node " << i << endl;
    depth[i] = d;
    par[i] = p;
    int c = 0;
    sub[i] = 1;
    for (int j: adj[i]) if (j != p) {
        dfs(j,i,d+1);
        sub[i] += sub[j];
        ++c;
        ++deg[i];
    }
    if (c == 0) {
        s.insert({depth[i],i}); 
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,1,0);
    /*
    for (auto p: s) {
        cout << p.first << ' ' << p.second << endl;
    }
    */
    while (k > 0) {
        auto p = *s.rbegin();
        s.erase(prev(s.end()));
        ans += p.first;
        //cout << p.second << endl;
        int i = p.second;
        if (--deg[par[i]] == 0) {
            //cout << "adding " << par[i] << ": " << depth[par[i]]-sub[par[i]]<< endl;
            s.insert({depth[par[i]]-sub[par[i]]+1,par[i]});
        }
        k--;
    }
    cout << ans << '\n';
}
