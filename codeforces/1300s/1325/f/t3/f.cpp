#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
vector<int> adj[maxn];
int target = 1;

int depth[maxn], par[maxn];
bool is[maxn];
vector<int> ind_set;
void dfs(int i, int p, int d) {
    par[i] = p;
    depth[i] = d;
    int mn = maxn;
    for (int j: adj[i]) {
        if (depth[j] == -1) continue;
        mn = min(mn,depth[j]);
    }
    if (depth[i]-mn >= target-1) {
        vector<int> cyc;
        int curr = i;
        while (true) {
            cyc.push_back(i);
            if (depth[i] == mn) break;
            i = par[i];
        }
        cout << 2 << '\n';
        cout << cyc.size() << '\n';
        for (auto j: cyc) {
            cout << j << ' ';
        }
        cout << '\n';
        exit(0);
    }
    for (int j: adj[i]) {
        if (depth[j] == -1) {
            dfs(j,i,d+1);
        }
    }
    bool can = true;
    for (int j: adj[i]) {
        if (is[j]) can = false;
    }
    if (can) {
        is[i] = true;
        ind_set.push_back(i);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    while (target*target < n) target++;
    memset(depth,-1,sizeof depth);
    dfs(1,1,0);
    cout << 1 << '\n';
    for (int i = 0; i < target; i++) {
        cout << ind_set[i] << ' ';
    }
    cout << '\n';
}
