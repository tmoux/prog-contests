#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
int parent[maxn]; //memset to -1
int mx_node[maxn];
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
    mx_node[x] = max(mx_node[x],mx_node[y]);
}

int getmax(int x) {
    return mx_node[Find(x)];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
        mx_node[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        Union(a,b);
    }
    int ans = 0;
    for (int i = n-1; i >= 1; i--) {
        int j = getmax(i);
        //cout << i << ' ' << j << endl;
        for (int k = j-1; k > i; k--) {
            if (Find(i) != Find(k)) {
                Union(i,k);
                ans++;
            }
        }
        mx_node[Find(i)] = i;
    }
    cout << ans << '\n';
}

