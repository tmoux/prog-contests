#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
vector<int> adj[maxn];
int cnt[maxn];
int depth[maxn];
ll ans = 0;

int c = 0;

void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    ans += 1LL*cnt[i]*depth[i];
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        cnt[i] += cnt[j];
    }
}

void dfs2(int i, int p, int del) {
    c += del;
    //cout << i << ": " << del << endl;
    set<pair<int,int>> ms;
    priority_queue<pair<int,int>> pq;
    ll tot = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        if (cnt[j] > 0) {
            pq.push({cnt[j],j});
            tot += cnt[j];
        }
    }
    if (cnt[i]-tot > 0) pq.push({cnt[i]-tot,i});
    for (int j = 0; j < del; j++) {
        pair<int,int> r = pq.top();
        pq.pop();
        if (r.first-1 > 0) pq.push({r.first-1,r.second});
    }
    while (pq.size() >= 2) {
        pair<int,int> r1 = pq.top(); pq.pop();
        pair<int,int> r2 = pq.top(); pq.pop();
        ans -= 2*depth[i];
        if (r1.first-1 > 0) pq.push({r1.first-1,r1.second});
        if (r2.first-1 > 0) pq.push({r2.first-1,r2.second});
    }
    /*
    for (auto p: ms) {
        cout << p.first << ' ' << p.second << endl;
    }
    */
    if (pq.empty()) return;
    else {
        auto pp = pq.top();
        if (pp.second == i) {
            ans -= 1LL*depth[i]*pp.first;
        }
        else {
            dfs2(pp.second,i,cnt[pp.second]-pp.first);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    cin >> n >> k;
    for (int i = 0; i < 2*k; i++) {
        int u; cin >> u;
        cnt[u]++;
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int start = (gen()%n)+1;
    depth[0] = -1;
    dfs(start,0);
    dfs2(start,0,0);    
    if (k == 100000) cout << "c = " << c << endl;
    cout << ans << '\n';
}
