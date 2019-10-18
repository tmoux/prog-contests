#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int q, n;
vector<int> adj[maxn];

bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        sub_size[i] += dfsSize(j,i);
    }
    return sub_size[i];
}

int getCentroid(int i, int p, int compSize) {
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        if (sub_size[j] * 2 > compSize) return getCentroid(j,i,compSize);
    }
    return i;
}

int f(int i, int p, bool start) {
    int sz = 0;
    multiset<int> pq;
    for (int j: adj[i]) {
        if (j == p) continue;
        sz++;
        if (blocked[j]) continue;
        pq.insert(f(j,i,0));
        if (pq.size() > (start?2:1)) pq.erase(pq.begin());
    }
    int sum = 0;
    for (int j: pq) sum += j;
    return sz + sum - (int)pq.size() + 1;
}

int decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    int res = f(centroid,centroid,1);
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        res = max(res,decomp(j));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> q;
    while (q--) {
        cin >> n;
        //reset
        for (int i = 1; i <= n; i++) {
            blocked[i] = false;
            sub_size[i] = 0;
            adj[i].clear();
        }
        for (int i = 0; i < n-1; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int ans = decomp(1);
        cout << ans << '\n';
    }
}
