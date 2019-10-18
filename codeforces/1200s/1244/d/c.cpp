#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int c[3][maxn];
vector<int> adj[maxn];
int deg[maxn];


int ret[maxn];
vector<int> v;
void getOrder(int i, int p) {
    v.push_back(i);
    for (int j: adj[i]) {
        if (j == p) continue;
        getOrder(j,i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    int start = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] >= 3) {
            cout << -1 << '\n';
            return 0;
        }
        if (deg[i] == 1) {
            start = i;
        }
    }
    assert(start != -1);
    getOrder(start,start);
    vector<int> perm = {0,1,2};
    ll ans = 1e18;
    do {
        ll tr = 0;
        for (int i = 0; i < n; i++) {
            tr += c[perm[i%3]][v[i]]; 
        }
        if (tr < ans) {
            ans = tr;
            for (int i = 0; i < n; i++) {
                ret[v[i]] = perm[i%3];
            }
        }
    } while (next_permutation(perm.begin(),perm.end()));
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        cout << (ret[i]+1) << ' ';
    }
    cout << '\n';
}

