#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int parent[maxn];
int dsu_find(int x) {
    return parent[x] < 0 ? x : parent[x] = dsu_find(parent[x]);
}
void dsu_union(int x, int y) {
    x = dsu_find(x), y = dsu_find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}
int comp_size(int x) {
    return -parent[dsu_find(x)];
}
int n, m, q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    memset(parent,-1,sizeof parent);
    while (q--) {
        char c; cin >> c;
        if (c == 'E') {
            int x, y; cin >> x >> y;
            x = dsu_find(x), y = dsu_find(y);
            cout << (x == y ? "Yes" : "No") << '\n';
        }
        else if (c == 'S') {
            int x; cin >> x;
            cout << comp_size(x) << '\n';
        }
        else {
            int x, y; cin >> x >> y;
            x = dsu_find(x), y = dsu_find(y);
            int cx = comp_size(x), cy = comp_size(y);
            if (x == y) {
                continue;
            }
            if (cx + cy <= m) {
                dsu_union(x,y);
            }
        }
    }

    return 0;
}

