#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M;
const int maxn = 1e5+5;
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
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        cin >> N >> M;
        for (int i = 1; i <= N; i++) {
            parent[i] = -1;
        }
        for (int i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            Union(a,b);
        }
        set<pair<int,int>> s;
        for (int i = 1; i <= N; i++) {
            int p = Find(i);
            int sz = -parent[p];
            s.insert({p,sz});
        }
        int ans = 0;
        for (auto p: s) {
            ans += p.second-1;
        }
        ans += 2*(s.size()-1);
        cout << ans << '\n';
    }
}
