#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 2e5+5;
int N, M;
vector<int> adj[maxn];
ll A[maxn], B[maxn];
int comp[maxn];

bool Less(pair<ll,ll> a, pair<ll,ll> b) {
    return a.first*b.second < b.first*a.second;
}

void dfs(int i, int pt, pair<ll,ll> mx) {
    comp[i] = pt;
    for (int j: adj[i]) {
        if (Less({A[j],B[j]},mx)) continue;
        if (comp[j] == -1) {
            dfs(j,pt,mx);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> N >> M;
        for (int i = 0; i <= N; i++) {
            adj[i].clear();
            comp[i] = -1;
        }
        for (int i = 1; i <= N; i++) cin >> A[i];
        for (int i = 1; i <= N; i++) cin >> B[i];
        for (int i = 1; i <= M; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        pair<pair<ll,ll>,int> mx = {{0,1},-1};
        for (int i = 1; i <= N; i++) {
            if (Less(mx.first,{A[i],B[i]})) {
                mx = {{A[i],B[i]},i};
            }
        }
        int pt = 0;
        //cout << mx.first.first << ' ' << mx.first.second << endl;
        for (int i = 1; i <= N; i++) {
            if (Less({A[i],B[i]},mx.first)) continue;
            if (comp[i] == -1) {
                //cout << "visiting " << i << endl;
                dfs(i,pt++,mx.first);
            }
        }
        map<int,vector<int>> mp;
        for (int i = 1; i <= N; i++) {
            if (comp[i] != -1) mp[comp[i]].push_back(i);
        }
        pair<int,int> best = {0,-1};
        for (auto& p: mp) {
            best = max(best,{p.second.size(),p.first});
        }
        cout << mp[best.second].size() << '\n';
        for (auto i: mp[best.second]) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
