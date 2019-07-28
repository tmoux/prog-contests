#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 5e5+5;
int n;
vector<int> adj[maxn];
int deg[maxn];
int tin[maxn];
int pt = 0;
 
vector<int> leafs;
void dfs(int i, int p) {
    tin[i] = pt++;
    if (deg[i] == 1) leafs.push_back(i);
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        ++deg[a];
        ++deg[b];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 1) {
            start = i;
        }
    }
    dfs(start,start);
    int k = leafs.size();
    int m = k/2;
    cout << (k+1)/2 << '\n';
    for (int i = 0; i < (k+1)/2; i++) {
        cout << leafs[i] << ' ' << leafs[(i+m)%k] << '\n';
    }
}
