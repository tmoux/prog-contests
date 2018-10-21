#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, m;
bool label[maxn], hasSelfLoop[maxn];
int parent[maxn];
int dsu_find(int x) {
    return parent[x] < 0 ? x : parent[x] = dsu_find(parent[x]);
}
void dsu_union(int x, int y) {
    x = dsu_find(x), y = dsu_find(y);
    if (x == y) return;
    if (x > y) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}
int comp_sz(int x) {
    return -parent[dsu_find(x)];
}
bool isValid(int x) {
    return hasSelfLoop[x] || comp_sz(x) > 1;
}

vector<int> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    memset(parent,-1,sizeof parent);
    string s; cin >> s;
    for (int i = 0; i < s.size(); i++) {
        label[i+1] = s[i] == 'A';
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;                
        if (u == v) hasSelfLoop[u] = true;
        if (!(label[u] ^ label[v])) dsu_union(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool works = false;
    for (int i = 1; i <= n && !works; i++) {
        if (isValid(i)) {
            for (int j: adj[i]) {
                if ((label[j] ^ label[i]) && isValid(j)) {
                    works = true;
                    break;
                }
            }
        }
    }
    cout << (works ? "Yes" : "No") << '\n';

    return 0;
}

