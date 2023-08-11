#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m, d, p[maxn];
vector<int> adj[maxn], dir[maxn];
int up[maxn], tr[maxn];
vector<int> down[maxn];

int get(vector<int>& vec, int x) {
    if (vec.size() >= 1 && vec.front() != x) return vec.front();
    else if (vec.size() >= 2) return vec[1];
    return -1;
}

void dfs1(int i, int pa) {
    tr[i] = p[i] ? 0 : -1;
    down[i].push_back(tr[i]);
    for (int j: adj[i]) {
        if (j == pa) continue;
        dir[i].push_back(j);
        dfs1(j,i);
        int x = tr[j] == -1 ? -1 : tr[j]+1;
        tr[i] = max(tr[i],x);
        down[i].push_back(x);
    }
    sort(down[i].begin(),down[i].end(),greater<int>());
}

void dfs2(int i, int pa) {
    up[i] = p[i] ? 0 : -1;
    if (i != pa) {
        up[i] = max(up[i],up[pa] == -1 ? -1 : up[pa]+1);
        int x = get(down[pa],tr[i]+1);
        if (x != -1) x++;
        up[i] = max(up[i],x);
    }
    for (int j: dir[i]) {
        dfs2(j,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> d;
    for (int i = 0; i < m; i++) {
        int pi; cin >> pi;
        p[pi] = 1;
    }
    for (int i = 1; i < n; i++) {
    	int u, v; cin >> u >> v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    dfs1(1,1);
    dfs2(1,1);
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": down: " << down[i] << " up: " << up[i] << '\n';
    }
    */
    int res = 0;
    for (int i = 1; i <= n; i++) {
        //cout << i << ": " << up[i] << ' ' << down[i].front() << '\n';
        if (max(up[i],down[i].front()) <= d) res++;
    }
    cout << res << '\n';

    return 0;
}
