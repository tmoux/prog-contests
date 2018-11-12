#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, q;
vector<int> adj[maxn];

map<int,int> parent;
map<int,vector<int>> childs;
map<int,int> xorP; //xor sum to parent
int Find(int x) {
    if (!parent.count(x)) parent[x] = -1;
    return parent[x] < 0 ? x : Find(parent[x]);
}

void recompute(int i, int x) {
    xorP[i] ^= x;
    for (int j: childs[i]) {
        recompute(j,x);
    }
}

void Union(int x, int y, int z) {
    int px = Find(x);
    int py = Find(y);
    assert(px != py);
    if (parent[px] > parent[py]) swap(px,py);
    parent[px] += parent[py];
    parent[py] = px;
    childs[px].push_back(py);
    //recalculate xor paths
    int a = xorP[x];
    int b = xorP[y];
    recompute(py,z^a^b);
}

void solve() {
    cin >> n >> q;
    parent.clear(); childs.clear(); xorP.clear();
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
    }
    while (q--) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 1) {
            int r; cin >> r;
            if (u == v) {
                cout << "WA\n";
            }
            else if (Find(u) != Find(v)) {
                Union(u,v,r);
                cout << "AC\n";
            }
            else {
                if (xorP[u] ^ xorP[v] == r) {
                    cout << "AC\n";
                }
                else {
                    cout << "WA\n";
                }
            }
        }
        else if (t == 2) {
            if (Find(u) != Find(v)) {
                cout << -1 << '\n';
            }
            else {
                cout << (xorP[u] ^ xorP[v]) << '\n';
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

