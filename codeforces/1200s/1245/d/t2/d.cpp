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
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        lit[i] = true;
        res += c[i];
    }
    for (int i = 0; i < n; i++) {
        pair<ll,int> best = {1e18,-1};
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (c[j] >= c[i]) continue;
            best = min(best,{dist[i][j],j});
        }
        if (c[i] > best.first) {
            res -= c[i];
            res += best.first;
            add_edge(i,best.second);
            lit[i] = false;
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
