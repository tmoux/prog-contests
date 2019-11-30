#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, c[maxn], k[maxn];
int x[maxn], y[maxn];
int mand(int x1, int y1, int x2, int y2) {
    return abs(x1-x2)+abs(y1-y2);
}
ll dist[maxn][maxn];

int parent[maxn]; //memset to -1
bool lit[maxn];
bool vis[maxn];

vector<pair<int,int>> ans;
void add_edge(int a, int b) {
    ans.push_back({a,b});
}
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int main() {
    memset(parent,-1,sizeof parent);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = 1LL*mand(x[i],y[i],x[j],y[j])*(k[i]+k[j]);
            //cout << i << ' ' << j << ": " << dist[i][j] << '\n';
        }
        dist[i][n] = dist[n][i] = c[i];
    }

    int u = n;
    lit[u] = true;
    vis[u] = true;
    vector<int> v;
    v.push_back(u);
    vector<ll> d(n+1);
    ll res = c[u];
    for (int i = 0; i <= n; i++) {
        d[i] = dist[u][i];
    }
    for (int i = 0; i < n; i++) {
        //find closest to any in v
        pair<ll,int> best = {1e18,-1};
        for (int j = 0; j <= n; j++) {
            if (vis[j]) continue;
            best = min(best,{d[j],j});
        }
        assert(best.second != -1);
        u = best.second;
        vis[u] = true;
        if (c[u] == best.first) {
            lit[u] = true;
            res += best.first;
        }
        else {
            int closest = -1;
            for (int j = 0; j < n; j++) {
                if (vis[j] && dist[u][j] == best.first) {
                    closest = j;
                    break;
                }
            }
            assert(closest != -1);
            add_edge(u,closest);
            res += best.first;
        }
        for (int j = 0; j < n; j++) {
            d[j] = min(d[j],dist[u][j]);
        }
    }

    vector<int> light;
    for (int i = 0; i < n; i++) {
        if (lit[i]) light.push_back(i);
    }
    //output
    cout << res << '\n';
    cout << light.size() << '\n';
    for (int i: light) {
        cout << (i+1) << ' ';
    }
    cout << '\n';
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first+1 << ' ' << p.second+1 << '\n';
    }
}
