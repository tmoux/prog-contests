#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;
int parent[maxn]; //memset to -1
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


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        Union(x,y);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i == Find(i)) {
            ans += (-parent[i]-1);
        }
    }
    cout << (k-ans) << '\n';
}

