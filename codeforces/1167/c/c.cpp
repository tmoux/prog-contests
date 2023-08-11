#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m;
int parent[maxn];

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
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    memset(parent,-1,sizeof parent);
    while (m--) {
        int k; cin >> k;
        if (k == 0) continue;
        //cout << k << endl;
        vector<int> v;
        while (k--) {
            int x; cin >> x;
            v.push_back(x);
        }
        for (int i = 0; i < v.size() - 1; i++) {
            Union(v[i],v[i+1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int sz = -parent[Find(i)];
        cout << sz << ' ';
    }
    cout << '\n';
}

