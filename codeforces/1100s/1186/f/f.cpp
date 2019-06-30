#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m;
int deg[maxn];
vector<int> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    vector<int> verts;
    for (int i = 1; i <= n; i++) {
        verts.push_back(i);
    }
    sort(verts.begin(),verts.end(),[](auto a, auto b) {
            return deg[a] > deg[b];
            });
}

